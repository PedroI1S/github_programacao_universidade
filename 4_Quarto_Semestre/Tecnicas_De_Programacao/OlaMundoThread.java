class OlaMundoThread extends Thread {
    private int id;
    
    public OlaMundoThread(int id) {
        this.id = id;
    }
    
    @Override
    public void run() {
        if (id < 10) {
            OlaMundoThread nextThread = new OlaMundoThread(id + 1);
            nextThread.start();
            try {
                nextThread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("Olá mundo, sou a thread Ola-" + String.format("%02d", id));
    }
    
    public static void main(String[] args) {
        OlaMundoThread firstThread = new OlaMundoThread(1);
        firstThread.start();
    }
}
