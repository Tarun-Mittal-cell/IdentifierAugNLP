import java.awt.*;
import java.awt.event.*;

public class MyFrame extends Frame {
    private Button btn;
    private TextField tf;

    public MyFrame() {
        super("MyFrame");
        btn = new Button("Click me");
        tf = new TextField(20);
        btn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                tf.setText("Button clicked");
            }
        });
        add(btn, BorderLayout.NORTH);
        add(tf, BorderLayout.CENTER);
        pack();
        setVisible(true);
    }

    public static void main(String[] args) {
        new MyFrame();
    }
}
