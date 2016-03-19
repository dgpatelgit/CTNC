package ctnc.homeiot.com.ctnc;

/**
 * Created by GokilaVani on 3/6/2016.
 */
public class Switch {
    public String getSwitchName() {
        return switchName;
    }

    public void setSwitchName(String switchName) {
        this.switchName = switchName;
    }

    public boolean isState() {
        return state;
    }

    public void setState(boolean state) {
        this.state = state;
    }

    public int getPictureId() {
        return pictureId;
    }

    public void setPictureId(int pictureId) {
        this.pictureId = pictureId;
    }

    private String switchName;
    private boolean state;
    private int pictureId;

}
