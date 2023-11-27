package test.cast;

import android.util.Log;

import android.content.Context;

import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.FutureTask;
import java.util.Optional;

import me.clarius.sdk.Cast;

public class CastWrapper {
    public static native void onConnected(boolean isConnected, long obj);

    private static final String TAG="CastWrapper";
    private Cast cast;
    private final ExecutorService pool;
    public CastWrapper(boolean anotherThread) {
        pool = anotherThread ? Executors.newFixedThreadPool(1) : null;
    }

    private Boolean innerCreateCast(Context ctx) {
        Log.d(TAG, String.format("innerCreateCast thread %d", Thread.currentThread().getId()));

        try {
            cast = new Cast(ctx, new CastListener());
            return true;
        } catch (Throwable e) {
            Log.e(TAG, "Failed instantiating cast", e);
            return false;
        }
    }

    private Boolean innerReleaseCast() {
        Log.d(TAG, String.format("innerReleaseCast thread %d", Thread.currentThread().getId()));

        if (cast != null)
        {
            try {
                cast.release();
                cast = null;
                return true;
            } catch (Throwable e) {
                Log.e(TAG, "Failed releasing cast", e);
                return false;
            }
        }
        return true;
    }

    private Boolean innerConnect(String ipAddress, int tcpport, long networkID, String certificate){
        if (cast != null)
        {
            System.out.println("ipAddress "+ipAddress);
            System.out.println("tcpport "+tcpport);
            System.out.println("networkID "+networkID);
            System.out.println("networkID "+certificate);

            try {
                Optional<Long> opNetworkId = Optional.ofNullable(networkID);//Utils.maybeLong(networkID);
                cast.connect(ipAddress, tcpport, opNetworkId, certificate, (result, port, swRevMatch) -> {
                     System.out.println("result "+result);
                    Log.d(TAG, "Connection result: " + result);
                    if (result) {
                        Log.d(TAG, "UDP stream will be on port " + port);
                        Log.d(TAG, "App software " + (swRevMatch ? "matches" : "does not match"));
                    }
                });

                return true;
            } catch (Throwable e) {
                Log.e(TAG, "Failed connect cast", e);
                return false;
            }
        }
        return false;
    }

    private boolean execute(Callable<Boolean> task) {
        
        if (pool != null) {
            Log.d(TAG, String.format("execute on a different thread %d", Thread.currentThread().getId()));
            FutureTask<Boolean> future = new FutureTask<>(task);
            pool.execute(future);
            try {
                return future.get();
            } catch (Throwable e) {
                Log.e(TAG, "Failed executing task", e);
                return false;
            }
        } else {
            Log.d(TAG, String.format("execute on the same thread %d", Thread.currentThread().getId()));
            try {
                return task.call();
            } catch (Throwable e) {
                Log.e(TAG, "Failed executing task", e);
                return false;
            }
        }
    }

    public boolean connect(String ipAddress, int port, long networkID, String certificate ){
        Callable<Boolean> callable = () -> innerConnect(ipAddress, port, networkID, certificate);
        return execute(callable);
    }

    public boolean test(String tt, int port, long networkID, long obj){
           System.out.println("tt "+tt);
           System.out.println("port "+port);
           System.out.println("port "+networkID);
           onConnected(false, obj);
           return true;
    }

    public boolean createCast(Context ctx) {
        Callable<Boolean> callable = () -> innerCreateCast(ctx);
        return execute(callable);
    }
    public boolean releaseCast() {
        Callable<Boolean> callable = () -> innerReleaseCast();
        return execute(callable);
    }

}
