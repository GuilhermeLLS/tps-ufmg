package com.company;

public class Block {
    int valid;
    String tag;
    String[] words;
    int dirty;

    Block() {
        words = new String[4];
        valid = 0;
        tag = "empty";
        dirty = 0;
    }
    public void write(String addressTag, int offset, String data) {
        valid = 1;
        dirty = 1;
        tag = addressTag;
        words[offset] = data;
    }
}
