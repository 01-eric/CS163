import java.util.*;
import java.io.*;

/* public class Test {
	
	public static void main(String[] args) {
		System.out.println(caesarCipher("PMG JIJM", 1100, false));
		System.out.println(vigenereCipher("ur bad", "hi", true));
	}
	
	static String caesarCipher(String s, int offset, boolean encrypt) {
		StringBuilder sb = new StringBuilder(s.length());
		for (char c : s.toCharArray()) if (Character.isLetter(c)) sb.append((char)((Character.toUpperCase(c) - 65 + (encrypt ? offset : 26 - (offset % 26))) % 26 + 65));
		return sb.toString();
	}
	
	// assume offset is valid string cuz I'm lazy
	static String vigenereCipher(String s, String key, boolean encrypt) {
		StringBuilder sb = new StringBuilder(s.length());
		for (int i = 0; i < s.length(); i++) {
			int offset = Character.toUpperCase(key.charAt(i % key.length())) - 65;
			if (Character.isLetter(s.charAt(i))) sb.append((char)((Character.toUpperCase(s.charAt(i)) - 65 + (encrypt ? offset : 26 - (offset % 26))) % 26 + 65));
		} return sb.toString();
	}
} */


public class Test {
	
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(new File("data1.txt"));
		double[] time = new double[101], speed = new double[101];
		for (int i = 0; i < time.length; i++) time[i] = Double.parseDouble(scanner.nextLine()) / 3600;
		for (int i = 0; i < speed.length; i++) speed[i] = Double.parseDouble(scanner.nextLine());
		System.out.println(trapezoid(time, speed) + "\n" + left(time, speed) + "\n" + right(time, speed));
	}
	
	static double trapezoid(double[] time, double[] speed) {
		double output = 0;
		for (int i = 0; i < time.length - 1; i++) output += (time[i + 1] - time[i]) * ((speed[i + 1] + speed[i]) / 2);
		return output;
	}
	
	static double left(double[] time, double[] speed) {
		double output = 0;
		for (int i = 0; i < time.length - 1; i++) output += (time[i + 1] - time[i]) * speed[i];
		return output;
	}
	
	static double right(double[] time, double[] speed) {
		double output = 0;
		for (int i = 1; i < time.length; i++) output += (time[i] - time[i - 1]) * speed[i];
		return output;
	}
	
}
