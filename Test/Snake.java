import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class Snake implements KeyListener, Runnable {
	
	static JFrame frame = new JFrame("Snake");
	static ArrayList<Point> snake = new ArrayList<Point>();
	static Point food;
	static int addToTail = 0;
	static GamePanel panel = new GamePanel();
	static boolean running = false;
	static enum Direction {UP, DOWN, LEFT, RIGHT, NONE};
	static Direction direction = Direction.NONE;
	
	public static void main(String[] args) {
		new Snake();
	}
	
	public Snake() {
		frame.setVisible(true);
		frame.setResizable(false);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1000, 1050);
		frame.setLayout(new BorderLayout());
		frame.add(panel, BorderLayout.CENTER);
		init();
		JOptionPane.showMessageDialog(frame, "Press space to pause. Use arrow keys to navigate. Press R to restart.");
		frame.addKeyListener(this);
	}
	
	public void keyTyped(KeyEvent e) {}
	public void keyReleased(KeyEvent e) {}
	public void keyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_SPACE && direction != Direction.NONE && !isDead()) {
			running = !running;
			if (running) new Thread(this).start();
		} else if (e.getKeyCode() == KeyEvent.VK_R) {
			running = false;
			Object[] options = {"Yes", "No"};
			if (JOptionPane.showOptionDialog(frame, "Are you sure you want to restart?", "Restart Game", JOptionPane.DEFAULT_OPTION, JOptionPane.WARNING_MESSAGE, null, options, options[0]) == 0) init();
			panel.repaint();
		} else {
			if (direction == Direction.NONE) { // game has not been started
				running = true;
				new Thread(this).start();
			} if (e.getKeyCode() == KeyEvent.VK_UP && direction != Direction.DOWN) direction = Direction.UP;
			else if (e.getKeyCode() == KeyEvent.VK_DOWN && direction != Direction.UP) direction = Direction.DOWN;
			else if (e.getKeyCode() == KeyEvent.VK_LEFT && direction != Direction.RIGHT) direction = Direction.LEFT;
			else if (e.getKeyCode() == KeyEvent.VK_RIGHT && direction != Direction.LEFT) direction = Direction.RIGHT;
		}
	}
	
	public void run() {
		while (running) {
			if (direction == Direction.UP) snake.add(0, new Point((int)snake.get(0).getX(), (int)snake.get(0).getY() - 1));
			else if (direction == Direction.DOWN) snake.add(0, new Point((int)snake.get(0).getX(), (int)snake.get(0).getY() + 1));
			else if (direction == Direction.LEFT) snake.add(0, new Point((int)snake.get(0).getX() - 1, (int)snake.get(0).getY()));
			else if (direction == Direction.RIGHT) snake.add(0, new Point((int)snake.get(0).getX() + 1, (int)snake.get(0).getY()));
			if (addToTail > 0) addToTail--;
			else snake.remove(snake.size() - 1);
			if (snake.get(0).getX() == food.getX() && snake.get(0).getY() == food.getY()) {
				addToTail += 5;
				while (containsKey(snake, food = new Point((int)(Math.random() * 45), (int)(Math.random() * 43))));
			} panel.repaint();
			if (isDead()) running = false;
			try {
				Thread.sleep(60);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static boolean isDead() {
		if (snake.get(0).getX() < 0 || snake.get(0).getX() >= 45 || snake.get(0).getY() < 0 || snake.get(0).getY() >= 43) return true;
		for (int i = 0; i < snake.size(); i++) for (int j = 0; j < snake.size(); j++) if (i != j && snake.get(i).getX() == snake.get(j).getX() && snake.get(i).getY() == snake.get(j).getY()) return true;
		return false;
	}
	
	private static boolean containsKey(ArrayList<Point> list, Point point) {
		for (Point p: list) if (p.getX() == point.getX() && p.getY() == point.getY()) return true;
		return false;
	}
	
	private static void init() {
		snake.clear();
		snake.add(new Point((int)(Math.random() * 45), (int)(Math.random() * 43)));
		while (containsKey(snake, food = new Point((int)(Math.random() * 45), (int)(Math.random() * 43))));
		direction = Direction.NONE;
		addToTail = 0;
	}

}

@SuppressWarnings({ "serial" })
class GamePanel extends JPanel {
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(Color.LIGHT_GRAY);
		g.fillRect(20, 62, 950, 908);
		for (int i = 0; i < 43; i++) for (int j = 0; j < 45; j++) fillGridSpot(j, i, new Color(0xD3D3D3), g);
		for (Point p: Snake.snake) fillGridSpot(p.getX(), p.getY(), new Color(0x006400), g);
		fillGridSpot(Snake.food.getX(), Snake.food.getY(), new Color(0xFFFF00), g);
		if (Snake.isDead()) fillGridSpot(Snake.snake.get(0).getX(), Snake.snake.get(0).getY(), new Color(0xFF0000), g);
		g.setColor(Color.DARK_GRAY);
		g.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 24));
		g.drawString("Length: " + Integer.toString(Snake.snake.size()), 860 - (int)Math.log10(Snake.snake.size()) * 13, 40);
	}
	
	static void fillGridSpot(double x, double y, Color color, Graphics g) {
		g.setColor(color);
		g.fillRect(25 + 21 * (int)x,  67 + 21 * (int)y, 16, 16);
	}
	
}
