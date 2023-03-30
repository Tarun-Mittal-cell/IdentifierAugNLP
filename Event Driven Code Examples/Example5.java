import javax.swing.*;
import java.awt.event.*;

public class MyFrame extends JFrame {
    private JButton btn;
    private JTextField tf;

    public MyFrame() {
        super("MyFrame");
        btn = new JButton("Click me");
        tf = new JTextField(20);
        btn.addActionListener(this::btnClicked);
        add(btn, BorderLayout.NORTH);
        add(tf, BorderLayout.CENTER);
        pack();
        setVisible(true);
    }

    private void btnClicked(ActionEvent e) {
        tf.setText("Button clicked");
    }

    public static void main(String[] args) {
        new MyFrame();
    }
}
