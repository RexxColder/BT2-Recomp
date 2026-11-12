import re,sys,glob,os
R='/mnt/Datos/Proyectos/BT2-Clean/BT2-Recomp/'
apply='--apply' in sys.argv
# callee arity from definitions/protos with params
ar={}
for f in glob.glob(R+'port/eq/*.c')+glob.glob(R+'src/**/*.c',recursive=True):
    try:t=open(f,errors='ignore').read()
    except:continue
    for m in re.finditer(r'^[A-Za-z_][\w \*]*?\b(\w+)\(([^)]*)\)\s*[;{]',t,re.M):
        p=m.group(2).strip()
        if p in('','void'):n=0
        else:n=p.count(',')+1
        ar[m.group(1)]=max(ar.get(m.group(1),0),n)
out=[];ch=0
idx={}
for sp in glob.glob(R+'scratch/m2c_sweep/*.s'):
    for l in open(sp):
        m=re.match(r'glabel (\w+)',l)
        if m:idx.setdefault(m.group(1),sp)
FILES=[f for f in glob.glob(R+'src/**/*.c',recursive=True) if not os.path.basename(f).startswith('auto_')]
for f in sorted(FILES):
    t=open(f).read()
    if not re.search(r'\b\w+\(\)',t):continue
    # split functions
    for fm in re.finditer(r'^[A-Za-z_][\w \*]*?\b(\w+)\(([^)]*)\)\s*\{',t,re.M):
        name,params=fm.group(1),fm.group(2)
        if name in('if','while','for','switch'):continue
        sp=idx.get(name)
        if not sp:continue
        asm=[l for l in open(sp) if re.match(r'\s*/\*',l)]
        ins=[]
        for l in asm:
            m=re.match(r'\s*/\*.*?\*/\s*(\S+)\s*(.*)',l)
            if m:ins.append((m.group(1),m.group(2).strip()))
        # body end
        start=fm.end();depth=1;i=start
        while depth and i<len(t):
            depth+= (t[i]=='{')-(t[i]=='}');i+=1
        body=t[start:i]
        pnames=re.findall(r'(\w+)\s*(?:,|$)',params) if params.strip() not in('','void') else []
        def wr(op,args,reg):
            if op in('sw','sd','sb','sh','swc1','sq','bnez','beqz','beq','bne','blez','bgtz','bgez','bltz','j','jr','nop','bnel','beql'):return False
            if op=='jal':return False
            return args.split(',')[0].strip()==reg
        seen_a0w=False
        for k,(op,args) in enumerate(ins):
            if op=='jal':
                callee=args
                cnt=sum(1 for q in re.finditer(r'\b%s\(\)'%re.escape(callee),body))
                if cnt==0:continue
                # a0 written in delay slot or previous 6?
                w=any(wr(*ins[j],'$a0') for j in range(max(0,k-6),min(len(ins),k+2)))
                a=ar.get(callee,0)
                out.append((f,name,callee,'a0writen' if w else 'A0PASS',seen_a0w,a,pnames[:1]))
            if wr(op,args,'$a0'):seen_a0w=True
        # apply
    if apply:
        pass
import collections
todo=collections.defaultdict(list); todo2=collections.defaultdict(list)
for o in out:
    if o[3]=='A0PASS' and not o[4] and o[5]>=1 and o[6]:todo[o[0]].append(o)
    elif o[3]=='A0PASS' and o[5]>=1 and not o[4] and not o[6]:todo2[o[0]].append(o)
    elif o[3]=='A0PASS' and o[5]>=1:print('SKIP',os.path.basename(o[0]),*o[1:])
n=0
for f,l in todo.items():
    t=open(f).read()
    for o in l:
        # replace within function body only
        fm=re.search(r'^[A-Za-z_][\w \*]*?\b%s\(([^)]*)\)\s*\{'%o[1],t,re.M)
        st=fm.end();d=1;i=st
        while d:
            d+=(t[i]=='{')-(t[i]=='}');i+=1
        body=t[st:i]
        nb=re.sub(r'\b%s\(\)'%re.escape(o[2]),'%s(%s)'%(o[2],o[6][0]),body)
        if nb!=body:t=t[:st]+nb+t[i:];n+=1
    if apply:open(f,'w').write(t)
n2=0
for f,l in todo2.items():
    t=open(f).read()
    for o in l:
        fm=re.search(r'^([A-Za-z_][\w \*]*?\b%s)\(\s*(?:void)?\s*\)\s*\{'%o[1],t,re.M)
        if not fm:continue
        st=fm.end();d=1;i=st
        while d:
            d+=(t[i]=='{')-(t[i]=='}');i+=1
        body=t[st:i]
        if 'arg0' in body:continue
        nb=re.sub(r'\b%s\(\)'%re.escape(o[2]),'%s(arg0)'%o[2],body)
        t=t[:fm.start()]+fm.group(1)+'(s32 arg0) {'+nb+t[i:];n2+=1
    if apply:open(f,'w').write(t)
print('sig-added',n2,file=sys.stderr)
print('files',len(todo),'repl',n,file=sys.stderr)
print(sum(1 for o in out if o[3]=='A0PASS'),'candidates / ',len(out),file=sys.stderr)
