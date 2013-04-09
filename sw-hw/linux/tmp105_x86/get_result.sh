#!/bin/sh

outputFolder=$1

if [ -z $1 ]
then 
  echo "Error: requires one parameter: $0 [Data folder]" 
  exit
fi

if [ ! -d $outputFolder ]; then
  echo "ERROR: Folder $outputFolder doesn't exist."
  exit
fi

# Compute total runtime in average
sum=0
size=`ls $outputFolder/data* | wc -l`
tmpFile=bc_tmp.txt

for f in `ls $outputFolder/data*`
do
    #echo "file: $f"
    time=`cat $f | grep "decision procedure" | cut -d \  -f 4 | cut -d s -f 1`
    #echo "$time + $sum"
    echo "$time + $sum" > $tmpFile
    echo "quit" >> $tmpFile
    sum=`bc $tmpFile | tail -n 1`
    #echo $sum
done

# Compute decision runtime in average
min_sum=0
sec_sum=0
tmpFile2=bc_tmp2.txt

grep real $outputFolder/runtime*.txt | 
while read line
do
   #echo $line
   time=`echo $line | cut -d \  -f 2`
   min=`echo $time | cut -d m -f 1`
   sec=`echo $time | cut -d m -f 2 | cut -d s -f 1`
   #echo $time
   #echo $min
   #echo $sec
   echo "$min + $min_sum" > $tmpFile
   echo "quit" >> $tmpFile
   min_sum=`bc $tmpFile | tail -n 1`
   echo "$sec + $sec_sum" > $tmpFile2
   echo "quit" >> $tmpFile2
   sec_sum=`bc $tmpFile2 | tail -n 1`
   #echo $min_sum
   #echo $sec_sum	
done

# Values of min_sum and sec_sum will remain after the for loop finishes
#for line in `grep real $outputFolder/runtime-$1.txt`
#do
#    if [ $line != "real" ] 
#    then
#        echo $line
#    fi
#done

#echo "($sum*1000)/$size" > $tmpFile
#echo "quit" >> $tmpFile
#avg=`bc $tmpFile | tail -n 1`

#echo min_sum
#echo sec_sum

# Values lost after the while loop finishes
min_sum=`bc $tmpFile | tail -n 1`
sec_sum=`bc $tmpFile2 | tail -n 1`

# Output results
echo "Runing experiment $size times took $min_sum minutes $sec_sum seconds in total."
echo "The decision procedure took $sum seconds in total."

#clean up
rm $tmpFile
rm $tmpFile2
