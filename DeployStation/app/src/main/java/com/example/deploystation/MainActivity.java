package com.example.deploystation;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.IntentSender;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.ResolvableApiException;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.location.LocationSettingsRequest;
import com.google.android.gms.location.LocationSettingsResponse;
import com.google.android.gms.location.LocationSettingsStatusCodes;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import org.eclipse.paho.android.service.MqttAndroidClient;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    HttpManager httpManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }

    final private int REQUEST_CODE_ASK_PERMISSIONS = 123;
    MainActivity mainActivity = this;

    public void init() {
        httpManager = new HttpManager(this);


        LocationRequest locationRequest = LocationRequest.create();
        locationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        LocationSettingsRequest.Builder builder = new LocationSettingsRequest.Builder()
                .addLocationRequest(locationRequest);

        Task<LocationSettingsResponse> result =
                LocationServices.getSettingsClient(this).checkLocationSettings(builder.build());


        result.addOnCompleteListener(new OnCompleteListener<LocationSettingsResponse>() {
            @Override
            public void onComplete(@NonNull Task<LocationSettingsResponse> task) {
                try {
                    LocationSettingsResponse response = task.getResult(ApiException.class);
                    // All location settings are satisfied. The client can initialize location
                    // requests here.
                } catch (ApiException exception) {
                    switch (exception.getStatusCode()) {
                        case LocationSettingsStatusCodes.RESOLUTION_REQUIRED:
                            // Location settings are not satisfied. But could be fixed by showing the
                            // user a dialog.
                            try {
                                // Cast to a resolvable exception.
                                ResolvableApiException resolvable = (ResolvableApiException) exception;
                                // Show the dialog by calling startResolutionForResult(),
                                // and check the result in onActivityResult().
                                resolvable.startResolutionForResult(
                                        mainActivity,
                                        LocationRequest.PRIORITY_HIGH_ACCURACY);
                            } catch (IntentSender.SendIntentException e) {
                                // Ignore the error.
                            } catch (ClassCastException e) {
                                // Ignore, should be an impossible error.
                            }
                            break;
                        case LocationSettingsStatusCodes.SETTINGS_CHANGE_UNAVAILABLE:
                            // Location settings are not satisfied. However, we have no way to fix the
                            // settings so we won't show the dialog.
                            break;
                    }
                }
            }
        });
        getLastKnownLocation();
    }

    LocationManager mLocationManager;

    Location currentLocation;
    private Location getLastKnownLocation() {
        mLocationManager = (LocationManager) getApplicationContext().getSystemService(LOCATION_SERVICE);
        LocationListener locationListener=new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                updateLocation(location);
            }

            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) {

            }

            @Override
            public void onProviderEnabled(String provider) {

            }

            @Override
            public void onProviderDisabled(String provider) {

            }
        };
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkSelfPermission(Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && checkSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED)
            {
                // TODO: Consider calling
                //    Activity#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for Activity#requestPermissions for more details.
                requestPermissions(new String[]{
                                Manifest.permission.ACCESS_FINE_LOCATION},
                        REQUEST_CODE_ASK_PERMISSIONS);
            }
            else
                {
                mLocationManager.requestLocationUpdates(
                        LocationManager.NETWORK_PROVIDER, 0, 0, locationListener);
            }
        }
//        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
//        {
//            if (checkSelfPermission(Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && checkSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED)
//            {
//                // TODO: Consider calling
//                //    Activity#requestPermissions
//                // here to request the missing permissions, and then overriding
//                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
//                //                                          int[] grantResults)
//                // to handle the case where the user grants the permission. See the documentation
//                // for Activity#requestPermissions for more details.
//                requestPermissions(new String[]{
//                                Manifest.permission.ACCESS_FINE_LOCATION},
//                        REQUEST_CODE_ASK_PERMISSIONS);
//            }
//            else
//            {
//
//                if (mLocationManager != null)
//                {
//                    currentLocation = mLocationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
//                    if(currentLocation != null && currentLocation.getTime() > Calendar.getInstance().getTimeInMillis() - 2 * 60 * 1000)
//                    {
//                        // Do something with the recent location fix
//                        //  otherwise wait for the update below
//                        Toast.makeText(mainActivity, "l: " + currentLocation, Toast.LENGTH_SHORT).show();
//                        return currentLocation;
//                    }
//                    else
//                    {
//                        Toast.makeText(mainActivity, "HERE", Toast.LENGTH_SHORT).show();
//                        mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, (long) 0, (float) 0, new LocationListener() {
//                            @Override
//                            public void onLocationChanged(Location location) {
//                                currentLocation=location;
//                            }
//
//                            @Override
//                            public void onStatusChanged(String provider, int status, Bundle extras) {
//
//                            }
//
//                            @Override
//                            public void onProviderEnabled(String provider) {
//
//                            }
//
//                            @Override
//                            public void onProviderDisabled(String provider) {
//
//                            }
//                        });
//                    }
//
//                }
//                else
//                {
//                    Toast.makeText(mainActivity, "mLocationManager = NULL", Toast.LENGTH_SHORT).show();
//                }
//            }
//        }
        Toast.makeText(mainActivity, "Current: "+currentLocation, Toast.LENGTH_SHORT).show();
        return currentLocation;
    }
    void updateLocation(Location location) {
        double longitude = location.getLongitude();
        double latitude = location.getLatitude();
        TextView textViewLat = findViewById(R.id.latitude);
        TextView textViewLong = findViewById(R.id.longtitude);

        textViewLat.setText(String.valueOf(latitude));
        textViewLong.setText(String.valueOf(longitude));
    }

    public void deploy(View v)
    {
        double lat=Double.valueOf(((TextView)findViewById(R.id.latitude)).getText().toString());
        double lon=Double.valueOf(((TextView)findViewById(R.id.longtitude)).getText().toString());
        String id=((TextView)findViewById(R.id.stationId)).getText().toString();
        httpManager.deploy(id,lat,lon);
    }

    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case REQUEST_CODE_ASK_PERMISSIONS:
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    Toast.makeText(mainActivity, "Granted", Toast.LENGTH_SHORT).show();
                    init();
                }
                else
                    {
                    // Permission Denied
                    Toast.makeText( this,"Allow permission" , Toast.LENGTH_SHORT)
                            .show();
                }
                break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case LocationRequest.PRIORITY_HIGH_ACCURACY:
                switch (resultCode) {
                    case Activity.RESULT_OK:
                        // All required changes were successfully made
                        Toast.makeText(mainActivity, "successful", Toast.LENGTH_SHORT).show();
                        init();
                        break;
                    case Activity.RESULT_CANCELED:
                        // The user was asked to change settings, but chose not to
                        Toast.makeText(mainActivity, "Nope", Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    @Override
    protected void onDestroy() {
        MqttAndroidClient client =httpManager.getMqttConnection().getAndroidClient();
        client.unregisterResources();
        client.close();
        super.onDestroy();
    }
    public void refresh(View v)
    {
        init();
    }

}
