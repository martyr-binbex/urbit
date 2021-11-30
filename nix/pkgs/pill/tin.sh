source $stdenv/setup

set -euo pipefail

ARVO=${ARVO?:ARVO location is unset}

cp -r $src ./pier
chmod -R u+rw ./pier

urbit -d ./pier

cleanup () {
  if [ -f ./pier/.vere.lock ]; then
    kill $(< ./pier/.vere.lock) || true
  fi
}

trap cleanup EXIT

echo "mounting"
# Update pill strategy to ensure correct staging
herb ./pier -p hood -d "+hood/mount /=base="

until [ -d ./pier/base ]; do
  sleep 1
done

# Update :lens, :dojo and dependencies
# FIXME: reduce this list
cp $ARVO/app/lens.hoon   ./pier/base/app/
cp $ARVO/app/dojo.hoon   ./pier/base/app/
cp $ARVO/lib/plume.hoon  ./pier/base/lib/
cp $ARVO/lib/server.hoon ./pier/base/lib/
cp $ARVO/lib/sole.hoon   ./pier/base/lib/
cp $ARVO/lib/xray.hoon   ./pier/base/lib/
cp $ARVO/lib/pprint.hoon ./pier/base/lib/

mkdir -p ./pier/base/mar/lens/

cp $ARVO/mar/lens/*      ./pier/base/mar/lens/

cp $ARVO/sur/lens.hoon   ./pier/base/sur/
cp $ARVO/sur/plum.hoon   ./pier/base/sur/
cp $ARVO/sur/sole.hoon   ./pier/base/sur/
cp $ARVO/sur/xray.hoon   ./pier/base/sur/

# Update +solid and its dependencies
cp $ARVO/lib/pill.hoon   ./pier/base/lib/
cp $ARVO/gen/solid.hoon  ./pier/base/gen/
cp $ARVO/gen/tin.hoon    ./pier/base/gen/
cp $ARVO/gen/tin2.hoon   ./pier/base/gen

chmod -R u+rw ./pier/base/

echo "commiting"

herb ./pier -p hood -d "+hood/commit %base"

echo "unmounting"

herb ./pier -p hood -d "+hood/unmount %base"

# FIXME: horrible hack to ensure the update is applied first
sleep 10

# Stage new desk for pill contents
echo "merge"
herb ./pier -p hood -d '+hood/merge %stage our %base'

echo "mount"

herb ./pier -p hood -d "+hood/mount /=stage="

until [ -d ./pier/stage ]; do
  sleep 1
done

echo "ls"
ls ./pier/stage 
echo "rm"
rm -rf ./pier/stage
echo "cp arvo to stage"
cp -r $ARVO ./pier/stage
echo "chmod"
chmod -R u+rw ./pier/stage

echo "commit"
herb ./pier -p hood -d "+hood/commit %stage"
#echo "unmount"
#herb ./pier -p hood -d "+hood/unmount %stage"
echo "+tin"
#herb ./pier -P solid.pill -d '+tin2 /=stage=/sys, =dub &'
herb ./pier -P tin.pill -d '+tin'
echo "exit"
herb ./pier -p hood -d '+hood/exit'

stopNest
