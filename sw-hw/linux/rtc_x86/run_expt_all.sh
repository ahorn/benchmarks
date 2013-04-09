#!/bin/bash
# Run experiment for Prop$2 to Prop$3 _once_ on the RTC SW/HW model
# where Prop$2 and Prop$3 range from 1 to 11
# Parse some command line input paramters, and verify they were set
exptName=$1
fromProp=$2
toProp=$3

if [[ -z $exptName || -z $fromProp || -z $toProp ]]
then
  echo "ERROR: Requires 3 arguments: $0 [Experiment Name] [From Property No.]  [To Property No.]"
  exit
fi

echo "Starting experiment from Prop$fromProp to Prop$toProp and name $exptName at " `date`

# Start the experiment
for i in `seq $fromProp $toProp`
do
  outputFolder="data"
  outputFile="$outputFolder/data-$exptName-prop$i.txt"
  runtimeFile="$outputFolder/runtime-$exptName-prop$i.txt"
  
  # Create directory for output files. Experiment will only be run if it will not overwrite an old data set
  if [ ! -d $outputFolder ]; then
    mkdir $outputFolder
  fi

  # Check if you have already run this data set
  if [ -s $outputFile ]; then
    echo "WARNING: File $outputFile already exists -- skipping verification of Prop$i"
    continue
  fi
 
  echo "Verifying Prop$i " `date`  

  export PROP_NO=$i

  # Put the commands to actually run your program / system here
  (time make verify &> $outputFile) &>> $runtimeFile

  # Possibly put some clean up steps here or a sleep command if you want a delay between experiments
  make clean
done

# Do any final cleanup here
echo "Finished at time " `date`
