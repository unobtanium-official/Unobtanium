### Seeds ###

Utility to generate the seeds.txt list that is compiled into the client
(see [src/chainparamsseeds.h](/src/chainparamsseeds.h) and [share/seeds](/share/seeds)).

### USAGE ###
Run the makeseeds.sh shell script to get list of current node IP's:
```
./makeseeds.sh
```
Then use the python script to insert the list into /src/chainparamsseeds.h:

```
python3 generate-seeds.py . > ../../src/chainparamsseeds.h
```


