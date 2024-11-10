CLEAN=false
RUN=false
RELEASE=false
RUN_PATH=""
for arg in "$@"; do
    if [ "$arg" == "--clean" ]; then
        CLEAN=true
    fi
    if [ "$arg" == "--release" ]; then
        RELEASE=true
    fi
    if [ "$arg" == "--run" ]; then
        RUN=true
    fi
done

if [ $CLEAN == true]; then
    echo ">> Cleaning first..."
    cd build && rm -fr * && mkdir Debug Release
    cd ..
    cd bin && rm -fr * && mkdir Debug Release
    cd ..
    echo
fi

if [ $RELEASE == true ]; then
    echo ">> Building Release..."
    cd build/Release
    cmake -DCMAKE_BUILD_TYPE=Release ../..
    cd ../..
    if [ $RUN == true ]; then
        RUN_PATH="bin/Release/SpaceshipTitanic"
    fi
else
    echo ">> Building Debug..."
    cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug ../..
    cmake --build .
    cd ../..
    rm compile_commands.json
    ln -s build/Debug/compile_commands.json compile_commands.json
    if [ $RUN == true ]; then
        RUN_PATH="bin/Debug/SpaceshipTitanic"
    fi
fi
echo

if [ -n "$RUN_PATH" ]; then
    echo ">> Running $RUN_PATH ..."
    ./$RUN_PATH
fi
echo
