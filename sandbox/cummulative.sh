rm -rf normal.txt
rm -rf slow.txt
for i in {0..10}
do
  ./trigger_bench.sh 50000
  sleep 1m
done