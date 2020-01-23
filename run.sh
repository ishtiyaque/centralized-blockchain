#! /bin/bash

num_client=3

cd server
make
gnome-terminal -- ./server
sleep 2
cd ../client
make

for (( id=1; id<=$num_client; id++ ))
do  
   sleep 2
   gnome-terminal -- "./client" $id
done

exit