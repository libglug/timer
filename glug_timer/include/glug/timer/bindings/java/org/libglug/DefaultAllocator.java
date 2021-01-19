package org.libglug;

import java.nio.ByteBuffer;

public class DefaultAllocator implements Allocator {
    public ByteBuffer malloc(int nbytes) {
        ByteBuffer bb = ByteBuffer.allocateDirect(nbytes);
        System.out.println("ByteBuffer capacity: " + bb.capacity());
        return bb;
    }

    public void free(ByteBuffer buffer) { }
}
