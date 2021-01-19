package org.libglug;

import java.nio.ByteBuffer;

public interface Allocator {
    ByteBuffer malloc(int nbytes);
    void free(ByteBuffer buffer);
}
