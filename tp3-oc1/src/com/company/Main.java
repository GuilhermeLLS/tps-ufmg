package com.company;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        String response;
        int address, operation;
        StringBuilder result = new StringBuilder();
        Memory mem = new Memory();
        Cache cache = new Cache(mem);
        DecimalFormat df = new DecimalFormat("#.###");
        df.setRoundingMode(RoundingMode.HALF_UP);
        try {
            File myObj = new File("../../../tests/" + args[0]);
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String[] splitString = myReader.nextLine().split(" ");
                address = Integer.parseInt(splitString[0]);
                operation = Integer.parseInt(splitString[1]);
                String binaryAddress = Long.toBinaryString(address & 0xffffffffL | 0x100000000L).substring(1);
                if(operation == 0) {
                    response = cache.read(binaryAddress);
                    result.append(String.join(" ", Integer.toString(address), Integer.toString(operation), response, "\n"));
                }
                if (operation == 1) {
                    response = cache.write(binaryAddress, splitString[2]);
                    result.append(String.join(" ", Integer.toString(address), Integer.toString(operation), splitString[2], response, "\n"));
                }
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        try {
            FileWriter fileStream = new FileWriter("results.txt");
            BufferedWriter myWriter = new BufferedWriter(fileStream);
            myWriter.write("READS: " + cache.reads);
            myWriter.newLine();
            myWriter.write("WRITES: " + cache.writes);
            myWriter.newLine();
            myWriter.write("HITS: " + cache.hits);
            myWriter.newLine();
            myWriter.write("MISSES: " + cache.misses);
            myWriter.newLine();
            myWriter.write("HIT RATE: " + df.format((double)(cache.hits) / cache.reads).replace(',', '.'));
            myWriter.newLine();
            myWriter.write("MISS RATE: " + df.format((double)(cache.misses) / cache.reads).replace(',', '.'));
            myWriter.newLine();
            myWriter.newLine();
            myWriter.write(result.toString());

            myWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }


    }
}
