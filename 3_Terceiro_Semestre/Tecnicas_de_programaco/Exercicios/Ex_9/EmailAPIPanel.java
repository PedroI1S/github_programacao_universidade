package Exercicios.Ex_9;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmailAPIPanel extends JFrame {
    private JTextField usernameField;
    private JButton loginButton;
    private JTextArea outputArea;
    private JButton writeButton;
    private JButton listButton;
    private JButton readButton;
    private JButton deleteButton;
    private JButton logoutButton;

    public EmailAPIPanel() {
        super("Email API Panel");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 300);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new GridLayout(7, 1));

        // Username input
        JPanel usernamePanel = new JPanel();
        usernamePanel.add(new JLabel("Username:"));
        usernameField = new JTextField(15);
        usernamePanel.add(usernameField);
        mainPanel.add(usernamePanel);

        // Login button
        loginButton = new JButton("Login");
        loginButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                // Perform login action
                outputArea.append("Logged in as " + username + "\n");
            }
        });
        mainPanel.add(loginButton);

        // Output area
        outputArea = new JTextArea(10, 30);
        outputArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(outputArea);
        mainPanel.add(scrollPane);

        // Write button
        writeButton = new JButton("Write Email");
        writeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Perform write email action
                outputArea.append("Writing email...\n");
            }
        });
        mainPanel.add(writeButton);

        // List button
        listButton = new JButton("List Emails");
        listButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Perform list emails action
                outputArea.append("Listing emails...\n");
            }
        });
        mainPanel.add(listButton);

        // Read button
        readButton = new JButton("Read Email");
        readButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Perform read email action
                outputArea.append("Reading email...\n");
            }
        });
        mainPanel.add(readButton);

        // Delete button
        deleteButton = new JButton("Delete Email");
        deleteButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Perform delete email action
                outputArea.append("Deleting email...\n");
            }
        });
        mainPanel.add(deleteButton);

        // Logout button
        logoutButton = new JButton("Logout");
        logoutButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Perform logout action
                outputArea.append("Logged out\n");
            }
        });
        mainPanel.add(logoutButton);

        getContentPane().add(mainPanel);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new EmailAPIPanel();
            }
        });
    }
}
