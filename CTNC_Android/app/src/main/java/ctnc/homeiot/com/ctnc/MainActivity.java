package ctnc.homeiot.com.ctnc;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;
import android.widget.TextView;


public class MainActivity extends ActionBarActivity {

    HorizontalScrollView hScrollView;
    TextView tViewRoom;
    static boolean alternate = false;
    private String rooms[] = {"Living Room", "Bed Room", "Kitchen"};
    private static int rotation_count;
    private LinearLayout left_arrow_layout, right_arrow_layout;
    private TextView rightArrow, leftArrow;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        rightArrow = (TextView)findViewById(R.id.right_arrow);
        leftArrow = (TextView)findViewById(R.id.left_arrow);
        right_arrow_layout = (LinearLayout)findViewById(R.id.right_arrow_layout);
        left_arrow_layout = (LinearLayout)findViewById(R.id.left_arrow_layout);

        hScrollView = (HorizontalScrollView)findViewById(R.id.mainScrollView);
        hScrollView.setHorizontalScrollBarEnabled(true);
        hScrollView.setOverScrollMode(View.OVER_SCROLL_ALWAYS);
        tViewRoom = (TextView)findViewById(R.id.textViewRoom);
        final Intent intent = new Intent(this, RoomActivity.class);
        tViewRoom.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(intent);
            }
        });
        hScrollView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                Log.d("KR", "Got msg: " + event.getAction() + " event: " + event);
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    if (!alternate) {
                        tViewRoom.setText("Bed Room");
                        alternate = true;
                    } else {
                        tViewRoom.setText("Living Room");
                        alternate = false;
                    }
                }
                return true;
            }
        });
        hScrollView.setOnGenericMotionListener(new View.OnGenericMotionListener() {
            @Override
            public boolean onGenericMotion(View v, MotionEvent event) {
                int e = event.getAction();
                Log.d("KR", "Got msg: " + event.getAction() + " event: " + event);
                // if(e == MotionEvent.ACTION_SCROLL){
                if (!alternate) {
                    tViewRoom.setText("Bed Room");
                    alternate = true;
                } else {
                    tViewRoom.setText("Living Room");
                    alternate = false;
                }

                //}
                return true;
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

        Button rulesButton = (Button)findViewById(R.id.rules_button);
        final Intent i = new Intent(this, RulesActivity.class);
        rulesButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(i);
            }
        });
    }

    private void leftRotation()
    {
        if (rotation_count > 0) {
            tViewRoom.setText(rooms[rotation_count]);
            rotation_count--;
        } else {
            rotation_count = rooms.length - 1;
        }
    }

    private void rightRotation()
    {
        if (rotation_count < 3) {
            tViewRoom.setText(rooms[rotation_count]);
            rotation_count++;
        } else {
            rotation_count = 0;
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
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
}
