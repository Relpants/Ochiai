Scapy

# Scapy

## API Reference
- https://scapy.readthedocs.io/en/latest/api/scapy.html


## Common Functions


### Async Sniffer
- Source Code - https://github.com/secdev/scapy/blob/master/scapy/sendrecv.py#L937-L1256

- `AsyncSniffer(iface="ifacename",count=x)`
	- Async sniffer constructor
- `AsyncSniffer.start()`
	- starts the sniffer
- `AsynSniffer.result()`
	- returns your packet list
