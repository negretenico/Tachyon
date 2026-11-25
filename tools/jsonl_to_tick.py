"""Convert Quantica order dump JSONL to binary .tick format.

Usage: py jsonl_to_tick.py order_20260723_1Hours.jsonl output.tick
"""
import json
import struct
import sys

MAGIC = b"TICK"
VERSION = 1
HEADER_FMT = "<4sHQ"         # magic(4) + version(2) + count(8) = 14 bytes
RECORD_FMT = "<QQQdd16sB7x"  # 64 bytes per record

def side_from_maker(m: bool) -> int:
    # m=true means buyer is maker, so taker is SELL
    # m=false means buyer is taker, so taker is BUY
    return 1 if m else 0

def convert(inpath: str, outpath: str):
    records = []
    with open(inpath, "r", encoding="utf-8") as f:
        for line in f:
            r = json.loads(line)
            sym = r["s"].encode("ascii")[:16].ljust(16, b"\x00")
            records.append((
                r["E"],              # event_time
                r["T"],              # trade_time
                r["t"],              # trade_id
                float(r["p"]),       # price
                float(r["q"]),       # quantity
                sym,                 # symbol
                side_from_maker(r["m"]),  # side
            ))

    records.sort(key=lambda t: t[0])

    with open(outpath, "wb") as f:
        f.write(struct.pack(HEADER_FMT, MAGIC, VERSION, len(records)))
        for rec in records:
            f.write(struct.pack(RECORD_FMT, *rec))

    print(f"{len(records)} ticks -> {outpath}")

if __name__ == "__main__":
    convert(sys.argv[1], sys.argv[2])
