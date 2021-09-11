package com.company;

public class Memory {
    String[] blocks;
    int indexSize;

    Memory() {
        blocks = new String[1024];
        indexSize = (int)(Math.log(1024) / Math.log(2));
    }

    public String read(String address) {
        return blocks[Integer.parseInt(address, 2)];
    }
    public void write(String address, String data) {
        blocks[Integer.parseInt(address, 2)] = data;
    }

}
