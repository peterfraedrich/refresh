# refresh
CLI tool that runs arbitrary commands at arbitrary intervals

```
usage: re [-h] [--number NUMBER] [--interval INTERVAL] [--nowipe]
          [--timeout TIMEOUT] [--debug] [--command ...]

Refresh runs arbitrary commands at arbitrary intervals.

optional arguments:
  -h, --help            show this help message and exit
  --number NUMBER, -n NUMBER
                        Number of times to loop. Defaults to infinite.
  --interval INTERVAL, -i INTERVAL
                        Number of seconds to wait between loops. Defaults to 1
                        second.
  --nowipe, -w          Don't wipe the screen after every loop
  --timeout TIMEOUT, -t TIMEOUT
                        Timeout (seconds) to wait for the process to finish.
                        Defaults to none.
  --debug, -d           Enables debug mode.
  --command ..., -c ...
                        The command to loop. Pipes and special characters must
                        be quoted!
```