#!/usr/bin/env python3
"""Cliente PINE minimo para PCSX2 (lectura/escritura de RAM EE)."""
import socket, struct, sys
SOCK = "/run/user/1000/.flatpak/net.pcsx2.PCSX2/xdg-run/pcsx2.sock"
class Pine:
    def __init__(self, path=SOCK):
        self.s = socket.socket(socket.AF_UNIX); self.s.connect(path)
    def _call(self, payload):
        self.s.sendall(struct.pack("<I", len(payload) + 4) + payload)
        n = struct.unpack("<I", self._rd(4))[0]
        body = self._rd(n - 4)
        if body[0] != 0: raise IOError("PINE error %d" % body[0])
        return body[1:]
    def _rd(self, n):
        b = b""
        while len(b) < n:
            c = self.s.recv(n - len(b))
            if not c: raise IOError("socket cerrado")
            b += c
        return b
    def r8(self, a):  return self._call(struct.pack("<BI", 0, a))[0]
    def r16(self, a): return struct.unpack("<H", self._call(struct.pack("<BI", 1, a)))[0]
    def r32(self, a): return struct.unpack("<I", self._call(struct.pack("<BI", 2, a)))[0]
    def w32(self, a, v): self._call(struct.pack("<BII", 6, a, v))
    def title(self):
        r = self._call(struct.pack("<B", 0xB)); return r[4:].rstrip(b"\0").decode()
    def status(self): return struct.unpack("<I", self._call(struct.pack("<B", 0xF)))[0]
    def read(self, a, n):
        return b"".join(struct.pack("<I", self.r32(a + i)) for i in range(0, n, 4))[:n]
if __name__ == "__main__":
    p = Pine(); print("title:", p.title(), "status:", p.status())
    a = int(sys.argv[1], 16) if len(sys.argv) > 1 else 0x100000
    print("%08x: %08x" % (a, p.r32(a)))
