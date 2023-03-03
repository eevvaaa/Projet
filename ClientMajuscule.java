import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class ClientMajuscule {

    public static void main(String[] args){
        try{
            Socket s = new Socket("localhost", 1240);

            PrintStream ps = new PrintStream(s.getOutputStream());
            BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));

            System.out.println(br.readLine());
            System.out.println(br.readLine());
            System.out.println(br.readLine());

            Scanner sc = new Scanner(System.in);
            ps.println(sc.nextLine());

            s.close();
            
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
