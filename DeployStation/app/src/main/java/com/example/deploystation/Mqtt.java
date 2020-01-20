package com.example.deploystation;

import android.app.Activity;
import android.content.Context;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class Mqtt{
    String clientId;
    MqttAndroidClient androidClient;
    Context context;
    public Mqtt(Context context)
    {
        this.context=context;
        this.clientId= MqttClient.generateClientId();
        this.androidClient= new MqttAndroidClient(context, "tcp://test.mosquitto.org:1883", clientId);
        connect();
    }

    private void connect() {
        try
        {
            IMqttToken token = androidClient.connect();
            token.setActionCallback(new IMqttActionListener() {

                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    subscribe("test_uid");
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    System.out.println("NOOOOOOOOOOOOOO==========");
                    Toast.makeText(context, "Error in connection: Timeout? Firewall?", Toast.LENGTH_SHORT).show();
//                    exception.printStackTrace();

                }
            });
        }
        catch (MqttException e)
        {
            Toast.makeText(context, "Error", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }
    }
    public void publish(String topic,String message)
    {
        byte[] encodedPayload = new byte[0];
        try
        {
            encodedPayload = message.getBytes("UTF-8");
            MqttMessage mqttMessage = new MqttMessage(encodedPayload);
            androidClient.publish(topic, mqttMessage);
        }
        catch (Exception e)
        {
            Toast.makeText(context, "Can't publish", Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }
    }
    public void subscribe(String topic)
    {
        Toast.makeText(context, "Subscribed", Toast.LENGTH_SHORT).show();
        int qos = 1;
        try
        {
            IMqttToken subToken = androidClient.subscribe(topic, qos);
            androidClient.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    Toast.makeText(context, "Connection Lost! Try Again", Toast.LENGTH_SHORT).show();
                }

                @Override
                public void messageArrived(String topic, MqttMessage message) throws Exception {
                    parseMqttMessage(topic,message);
                    Toast.makeText(context, "Recieved", Toast.LENGTH_SHORT).show();
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {

                }
            });
            subToken.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {

                }

                @Override
                public void onFailure(IMqttToken asyncActionToken,
                                      Throwable exception) {
                    Toast.makeText(context, "Can't subscribe! User authorization?", Toast.LENGTH_SHORT).show();

                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    private void parseMqttMessage(String topic, MqttMessage mqttMessage) {
        String stationUID=mqttMessage.toString();
        Toast.makeText(context, "Message: "+mqttMessage, Toast.LENGTH_SHORT).show();

        LinearLayout linearLayout=((MainActivity)context).findViewById(R.id.layout);
        TextView textViewId =(linearLayout).findViewById(R.id.stationId);
        textViewId.setText(stationUID);
    }

    public MqttAndroidClient getAndroidClient() {
        return androidClient;
    }
}
