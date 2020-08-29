#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/ravi/classic_ur_ws/src/track_ik/trac_ik_python"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/ravi/classic_ur_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/ravi/classic_ur_ws/install/lib/python2.7/dist-packages:/home/ravi/classic_ur_ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/ravi/classic_ur_ws/build" \
    "/usr/bin/python" \
    "/home/ravi/classic_ur_ws/src/track_ik/trac_ik_python/setup.py" \
    build --build-base "/home/ravi/classic_ur_ws/build/track_ik/trac_ik_python" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/ravi/classic_ur_ws/install" --install-scripts="/home/ravi/classic_ur_ws/install/bin"
