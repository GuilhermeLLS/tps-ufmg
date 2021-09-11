package com.company;

import java.util.Objects;

public class Cache {
    int INDEX_SIZE = 6;
    int OFFSET_SIZE = 4;
    int TAG_SIZE = 32 - INDEX_SIZE - OFFSET_SIZE;
    int hits;
    int misses;
    int reads;
    int writes;
    Block[] blocks;
    Memory memory;

    Cache(Memory mem) {
        blocks = new Block[64];
        for (int i = 0; i < 64; i++) {
            blocks[i] = new Block();
        }
        memory = mem;
        hits = 0;
        misses = 0;
        reads = 0;
        writes = 0;
    }

    public String parseIndex(String address) {
        return address.substring(TAG_SIZE, INDEX_SIZE + TAG_SIZE);
    }

    public String parseTag(String address) {
        return address.substring(0, TAG_SIZE);
    }

    public String parseOffset(String address) {
        return address.substring(INDEX_SIZE, OFFSET_SIZE + INDEX_SIZE);
    }

    public String read(String address) {
        int index = Integer.parseInt(parseIndex(address), 2);
        String tag = parseTag(address);
        if (blocks[index].valid == 1 && Objects.equals(blocks[index].tag, tag)) {
            hits++;
            reads++;
            return "H";
        } else {
            readFromMemory(address);
            misses++;
            reads++;
            return "M";
        }
    }

    public String parseDecimalToBin(int decNumber) {
        String num = Integer.toString(decNumber, 2);
        return num.length() == 1 ? "0"+num : num;
    }

    public void readFromMemory(String address) {
        String stringedIndex = parseIndex(address);
        int index = Integer.parseInt(stringedIndex, 2);
        String tag = parseTag(address);

        for (int wordOffset = 0; wordOffset < 4; wordOffset++) {
            blocks[index].words[wordOffset] = memory.read(tag + parseIndex(address) + parseDecimalToBin(wordOffset));
        }
        blocks[index].tag = tag;
        blocks[index].valid = 1;
    }

    public String write(String address, String data) {
        int index = Integer.parseInt(parseIndex(address), 2);
        String tag = parseTag(address);
        int offset = Integer.parseInt(parseOffset(address), 2);

        if(blocks[index].dirty == 1)  {
            writeBack(address, data);
        }
        blocks[index].write(tag, offset, data);
        writes++;
        return "W";
    }

    public void writeBack(String address, String data) {
        memory.write(address, data);
        int index = Integer.parseInt(parseIndex(address), 2);
        blocks[index].dirty = 0;
    }

}
