#!/bin/bash

id=0
ih=40
for f in images/img0*; do 
   sleep 1 
   clear
   sed -n "${id},${ih}p;$((ih + 1))q"  $f | cut -c1-200 |sed 's/ //g' | sed 's/0/ /g' | sed 's/1/@/g' | sed 's/1/@/g'
   id=$(( id + 1))
   ih=$(( ih + 1))
done
