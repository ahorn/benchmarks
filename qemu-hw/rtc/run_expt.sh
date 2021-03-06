# Simple Experiment Script
# by T.W.W. - Public Domain 2011

# Parse some command line input paramters, and verify they were set
numberOfRuns=$1
exptName=$2
export PROP_NO=$3
outputFolder="data/output-$2-prop$3"
runtimeFile="$outputFolder/runtime-$2-prop$3.txt"

if [[ -z $numberOfRuns || -z $exptName || -z $3 ]]
then
  echo "ERROR: Requires 4 arguments: $0 [Num of Runs] [Experiment Name] [Property No.]"
  exit
fi

# Create directory for output files. Experiment will only be run if it will not overwrite an old data set
if [ -d $outputFolder ]; then
  echo "ERROR: Folder $outputFolder already exists."
  exit
else
  mkdir $outputFolder
fi

echo "Starting experiment with $numberOfRuns iterations and name $exptName at " `date`

# Repeat the experiment $numberOfRuns times
for i in `seq $numberOfRuns`
do
  # Check if you have already run this data set
  outputFile="$outputFolder/data-$exptName-prop$3-$i.txt"
  if [ -s $outputFile ]
  then
    echo "WARNING: File $outputFile already exists -- skipping run $i"
    continue
  fi

  echo "Running iteration $i " `date`
  # Set loop unwinding number  
  if [[ $3 == 1  || $3 == 2 ]]; then
    export UNWIND=11
  else 
    export UNWIND=1
  fi 

  # Put the commands to actually run your program / system here
  (time make verify &> $outputFile) &>> $runtimeFile
  # Possibly put some clean up steps here or a sleep command if you want a delay between experiments
  make clean
done

# Do any final cleanup here
echo "Finished at time " `date`
