MOST_RECENT_FILE=$1
echo $MOST_RECENT_FILE
../../raw2tree_bsd_GSE/raw2tree_bsd_GSE $MOST_RECENT_FILE
ROOT_FILE=$MOST_RECENT_FILE"_tree.root"
echo $ROOT_FILE
DIRECTORY=$1_dir
mkdir $DIRECTORY
mv $ROOT_FILE $DIRECTORY
mv $MOST_RECENT_FILE $DIRECTORY
cp scripts/plot_all.C $DIRECTORY
cd $DIRECTORY
root -l $ROOT_FILE ../scripts/plot_all.C
