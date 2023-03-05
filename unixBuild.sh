mkdir -p unixBuild
cd unixBuild
cmake -S ../ -B . -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=1
rm ../compile_commands.json
mv compile_commands.json ..
if make; then
    cd .. && ./unixBuild/rtow linuxImage.ppm
else
    cd ..
fi
