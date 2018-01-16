/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Presentation;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

/**
 *
 * @author rafae
 */
public class ConfigReader {
    
    private static final String STARTED = "started";
    private static final String FILE = "config.txt";
    
    
    public static boolean readFile() {
        boolean b = false;
        
        List<String> list = new ArrayList<>();

	try (Stream<String> stream = Files.lines(Paths.get(FILE))) {
            stream.forEach(line -> { list.add(line); });
            
            for (String line : list) {
                if (line.startsWith(STARTED)) {
                    String[] parts = line.split("=");
                    b = (Integer.parseInt(parts[1]) > 0);
                    break;
                }   
            }
                
        } catch (Exception e) {
            return false;
        }

        return b;
    }
}
