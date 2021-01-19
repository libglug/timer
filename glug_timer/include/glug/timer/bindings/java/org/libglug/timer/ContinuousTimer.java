package org.libglug.timer;

import java.nio.ByteBuffer;
import org.libglug.Allocator;

public class ContinuousTimer {
    static {
        System.loadLibrary("glug_timer");
    }

    public ContinuousTimer(Allocator allocator) {
        timerImpl = alloc(allocator);
    }

    public void close() {
        free(timerImpl);
    }

    public void start() {
        start(timerImpl);
    }

    public void pause() {
        pause(timerImpl);
    }

    public void reset() {
        reset(timerImpl);
    }

    public void delta(Time delta) {
        delta(timerImpl, delta);
    }

    public void runTime(Time run) {
        runTime(timerImpl, run);
    }

    public State state() {
        return stateValues[state(timerImpl)];
    }

    public static void resolution(Time res) {
        res(res);
    }

    private ByteBuffer timerImpl;

    private native ByteBuffer alloc(Allocator allocator);
    private native void free(ByteBuffer timerImpl);

    private native void start(ByteBuffer timerImpl);
    private native void pause(ByteBuffer timerImpl);
    private native void reset(ByteBuffer timerImpl);

    private native void delta(ByteBuffer timerImpl, Time delta);
    private native void runTime(ByteBuffer timerImpl, Time run);

    private native int  state(ByteBuffer timerImpl);
    private native static void res(Time res);

    private final State[] stateValues = State.values();
}
