import java.util.*;

public class Test {
	
	public static void main(String[] args) {
		System.out.println(caesarCipher("PMGJIJM", 1100, false));
		System.out.println(vigenereCipher("ur a", "hi", true));
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
}

