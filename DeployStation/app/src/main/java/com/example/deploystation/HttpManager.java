package com.example.deploystation;

import android.content.Context;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONObject;

import java.util.ArrayList;


public class HttpManager {
    String url="https://territoire.emse.fr/applications/air-quality-control/station-info";
    RequestQueue queue;
    Context context;
    Mqtt mqttConnection;
    public HttpManager(Context context) {
        this.context = context;
        mqttConnection=new Mqtt(context);
        queue = Volley.newRequestQueue(context);
    }
    public void deploy(final String id, double lat, double lon)
    {
        try
        {
            JSONObject obj = new JSONObject();
            JSONObject data=new JSONObject();
            data.put("station_id",id);
            data.put("latitude",lat);
            data.put("longitude",lon);
            obj.put("data",data);
            JsonObjectRequest postRequest = new JsonObjectRequest(Request.Method.POST, url, obj,
                    new Response.Listener<JSONObject>()
                    {
                        @Override
                        public void onResponse(JSONObject response) {
                            mqttConnection.publish(id,"OK");
                            Toast.makeText(context, "Published", Toast.LENGTH_SHORT).show();
                        }
                    },
                    new Response.ErrorListener()
                    {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            error.printStackTrace();
                            Toast.makeText(context, "ERROR", Toast.LENGTH_SHORT).show();
                        }
                    }
            );
            queue.add(postRequest);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public Mqtt getMqttConnection() {
        return mqttConnection;
    }
}
