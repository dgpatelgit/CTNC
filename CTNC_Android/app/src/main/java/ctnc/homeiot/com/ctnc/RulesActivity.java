package ctnc.homeiot.com.ctnc;

import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;


public class RulesActivity extends ActionBarActivity {

    private Button clearButton, defaultButton, virtualWireButton, timingButton, nightMode, motionSensor;
    InetAddress inet_addr ;
    DatagramSocket socket;
    String sendCommand;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rules);
        clearButton = (Button)findViewById(R.id.button_clear);
        defaultButton = (Button)findViewById(R.id.button2);
        virtualWireButton = (Button)findViewById(R.id.button3);
        timingButton = (Button)findViewById(R.id.button4);
        nightMode = (Button)findViewById(R.id.button5);
        motionSensor = (Button)findViewById(R.id.button6);
        clearButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new ATcommandThread().execute("/11/1112/456/rvw/0");
            }
        });

        defaultButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new ATcommandThread().execute("/11/1112/456/rvw/0");
                new ATcommandThread().execute("/11/1112/456/avw/1/PYWZRZKKX/1/PYWZRZKKX/5");
                new ATcommandThread().execute("/11/1112/456/avw/1/PYWZRZKKX/2/PYWZRZKKX/4");
                new ATcommandThread().execute("/11/1112/456/avw/1/PYWZRZKKX/3/PYWZRZKKX/6");
            }
        });

        virtualWireButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new ATcommandThread().execute("/11/1112/456/rvw/0");
                new ATcommandThread().execute("/11/1112/456/avw/1/PYWZRZKKX/1/PYWZRZKKX/5");
                new ATcommandThread().execute("/11/1112/456/avw/1/PYWZRZKKX/2/PYWZRZKKX/6");
                new ATcommandThread().execute("/11/1112/456/avw/1/PYWZRZKKX/3/PYWZRZKKX/4");
            }
        });

        timingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new ATcommandThread().execute("/11/1112/456/rtmr/0");
                new ATcommandThread().execute("/11/1112/456/atmr/2/3000/0");
            }
        });

        nightMode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new ATcommandThread().execute("/11/1112/456/avw/2/PYWZRZKKX/2/PYWZRZKKX/3");
            }
        });

        motionSensor.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new ATcommandThread().execute("/11/1112/456/avw/1/PYWZRZKQP/1/PYWZRZKKX/2");
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_rules, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public class ATcommandThread extends AsyncTask<String, Integer, Boolean> {

        @Override
        protected Boolean doInBackground(String... arg0) {

            byte[] ip_bytes = new byte[]{(byte) 192, (byte) 168, (byte) 0, (byte) 255};

            try {
                inet_addr = InetAddress.getByAddress(ip_bytes);
            } catch (UnknownHostException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            Log.e("AT command: ", "at_cmd) + arg0:" + arg0[0].toString());
            byte[] buffer;

            buffer = arg0[0].getBytes();

            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, inet_addr, 5656);
            try {
                socket = new DatagramSocket();
                socket.send(packet);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            Log.e("///send at command", "at command topic");
            return null;
        }
    }

}
