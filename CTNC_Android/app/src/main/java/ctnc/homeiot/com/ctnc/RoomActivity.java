package ctnc.homeiot.com.ctnc;

import android.os.AsyncTask;
import android.os.StrictMode;
import android.support.v7.app.ActionBarActivity;
import android.app.ActionBar.LayoutParams;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.HorizontalScrollView;
import android.widget.ImageSwitcher;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.ToggleButton;
import android.widget.ViewSwitcher;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Enumeration;


public class RoomActivity extends ActionBarActivity {

    LinearLayout lLayout, room_layout, image_layout, left_arrow_layout, right_arrow_layout;
    private ImageSwitcher sw;
    private HorizontalScrollView hScrollView;
    private TextView switchName, rightArrow, leftArrow;
    private String[] electric_devices = {"Orange Light", "Blue Light", "Plug"};
    private int[] image_ids = {R.drawable.orange_on, R.drawable.blue_on, R.drawable.switch_board,
                                R.drawable.orange_off, R.drawable.blue_off, R.drawable.switch_board};
    public static int rotation_count = 0;
    private Switch switchControl;
    private String[] udp_commands = {"/11/1112/456/sresval/1","/11/1112/456/sresval/2","/11/1112/456/sresval/3"};
    private InetAddress IPAddress;
    byte[] send_data = new byte[1024];
    DatagramSocket client_socket;
    InetAddress inet_addr ;
    DatagramSocket socket;
    public static boolean buttonOn;
    public static boolean[] switchStatus = {false,false, false};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        int image_end_pos, room_end_pos;

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_room);
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
                .permitAll().build();
        StrictMode.setThreadPolicy(policy);

        lLayout = (LinearLayout)findViewById(R.id.switch_addition);
        room_layout = (LinearLayout)findViewById(R.id.layout_room);
        image_layout = (LinearLayout)findViewById(R.id.layout_switch_image);
        switchName = (TextView)findViewById(R.id.text_switch_name);
        rightArrow = (TextView)findViewById(R.id.right_arrow);
        leftArrow = (TextView)findViewById(R.id.left_arrow);
        right_arrow_layout = (LinearLayout)findViewById(R.id.right_arrow_layout);
        left_arrow_layout = (LinearLayout)findViewById(R.id.left_arrow_layout);
        sw = (ImageSwitcher) findViewById(R.id.imageSwitcher);
        sw.setFactory(new ViewSwitcher.ViewFactory() {
            @Override
            public View makeView() {
                ImageView myView = new ImageView(getApplicationContext());
                myView.setScaleType(ImageView.ScaleType.FIT_CENTER);
                myView.setLayoutParams(new ImageSwitcher.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
                return myView;
            }
        });
        Animation in = AnimationUtils.loadAnimation(this, android.R.anim.slide_in_left);
        Animation out = AnimationUtils.loadAnimation(this, android.R.anim.slide_out_right);
        sw.setInAnimation(in);
        sw.setOutAnimation(out);

        image_end_pos = image_layout.getBottom();
        room_end_pos = room_layout.getBottom();
        //lLayout.setPadding(0, (room_end_pos - image_end_pos + 100), 0, 0);

        hScrollView = (HorizontalScrollView)findViewById(R.id.mainScrollView);
        hScrollView.setHorizontalScrollBarEnabled(true);
        hScrollView.setOverScrollMode(View.OVER_SCROLL_ALWAYS);

        hScrollView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                Log.d("KR", "Got msg: " + event.getAction() + " event: " + event);
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    leftRotation();
                }
                return true;
            }
        });

        ToggleButton t = (ToggleButton)findViewById(R.id.toggleButton);
        t.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });

        t.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                Socket socket = null;
                DataOutputStream dataOutputStream = null;
                if (isChecked) {
                    buttonOn = true;
                    switchStatus[rotation_count] = true;
                } else {
                    buttonOn = false;
                    switchStatus[rotation_count] = false;
                }

                new ATcommandThread().execute(String.valueOf(isChecked));
            }
        });
        left_arrow_layout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                leftRotation();
            }
        });
        leftArrow.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                leftRotation();
            }
        });
        right_arrow_layout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                rightRotation();
            }
        });
        rightArrow.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                rightRotation();
            }
        });
    }


    private void leftRotation()
    {
        if (rotation_count >= 0) {
            switchName.setText(electric_devices[rotation_count]);
            if(switchStatus[rotation_count]){
                sw.setImageResource(image_ids[rotation_count]);
            }else{
                sw.setImageResource(image_ids[rotation_count+3]);
            }
            ToggleButton t = (ToggleButton)findViewById(R.id.toggleButton);
            t.setChecked(switchStatus[rotation_count]);

            rotation_count--;
        }
        if(rotation_count <= 0) {
            rotation_count = electric_devices.length - 1;
        }

    }

    private void rightRotation()
    {
        if (rotation_count < 3) {
            switchName.setText(electric_devices[rotation_count]);
            if(switchStatus[rotation_count]){
                sw.setImageResource(image_ids[rotation_count]);
            }else{
                sw.setImageResource(image_ids[rotation_count+3]);
            }
            ToggleButton t = (ToggleButton)findViewById(R.id.toggleButton);
            t.setChecked(switchStatus[rotation_count]);


            rotation_count++;
        }
        if(rotation_count >= 3) {
            rotation_count = 0;
        }

    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_room, menu);
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

/*
    public void toggleButtonOnClick(View v) {
  try {
            client_socket = new DatagramSocket(5656);
        } catch (SocketException e) {
            e.printStackTrace();
        }
        try {
            IPAddress = InetAddress.getByName("192.168.1.255");
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        ToggleButton t = (ToggleButton)v;
        boolean isChecked = ((ToggleButton) v).isChecked();
        if(isChecked){
            send_data = (udp_commands[rotation_count]+"/1").getBytes();
            Log.d("KR::", "send_data:" + udp_commands[rotation_count] + "/1");
            DatagramPacket send_packet = new DatagramPacket(send_data,udp_commands[rotation_count].length()+2,
                    IPAddress, 5656);
            Log.d("KR::","after send_data:"+ send_packet.getData() );
            try{
                client_socket.send(send_packet);
            }catch (IOException iOE){

            }
        }
        else{
            send_data = (udp_commands[rotation_count]+"/0").getBytes();
            DatagramPacket send_packet = new DatagramPacket(send_data,udp_commands[rotation_count].length()+2,
                    IPAddress, 5656);
            try{
                client_socket.send(send_packet);
            }catch (IOException iOE){

            }
        }

        Socket socket = null;
        DataOutputStream dataOutputStream = null;
        try {
            socket = new Socket("192.168.1.255", 5656);
            dataOutputStream = new DataOutputStream(socket.getOutputStream());
            dataOutputStream.writeUTF(udp_commands[rotation_count] + "/1");
            Log.d("KR::", "after send_data:");

        } catch (UnknownHostException e) {

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (socket != null) {
                try {
                    socket.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }

            if (dataOutputStream != null) {
                try {
                    dataOutputStream.close();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }
*/

    public class ATcommandThread extends AsyncTask<String, Integer, Boolean> {

        @Override
        protected Boolean doInBackground(String... arg0) {

//            String broadcastAddress = getBroadcast();
//            Log.e("KR ", "broadcastAddress: "+broadcastAddress);
            byte[] ip_bytes = new byte[]{(byte) 192, (byte) 168, (byte) 0, (byte) 255};

            try {
                inet_addr = InetAddress.getByAddress(ip_bytes);
            } catch (UnknownHostException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            Log.e("AT command: ", "at_cmd) + arg0:" + arg0.toString());
            byte[] buffer;
            if(buttonOn) {
                buffer = (udp_commands[rotation_count] + "/1" + "\r").getBytes();
                Log.e("KR: ","buttonOn");
            }else{
                buffer = (udp_commands[rotation_count] + "/0" + "\r").getBytes();
                Log.e("KR: ","buttonOff");
            }
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

    public static String getBroadcast(){
        String found_bcast_address=null;
        System.setProperty("java.net.preferIPv4Stack", "true");
        try
        {
            Enumeration<NetworkInterface> niEnum = NetworkInterface.getNetworkInterfaces();
            while (niEnum.hasMoreElements())
            {
                NetworkInterface ni = niEnum.nextElement();
                if(!ni.isLoopback()){
                    for (InterfaceAddress interfaceAddress : ni.getInterfaceAddresses())
                    {

                        found_bcast_address = interfaceAddress.getBroadcast().toString();
                        found_bcast_address = found_bcast_address.substring(1);

                    }
                }
            }
        }
        catch (SocketException e)
        {
            e.printStackTrace();
        }

        return found_bcast_address;
    }
}
