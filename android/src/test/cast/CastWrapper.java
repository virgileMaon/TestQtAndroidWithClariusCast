package test.cast;

import android.util.Log;

import android.content.Context;

import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.FutureTask;

import me.clarius.sdk.Cast;

public class CastWrapper {
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

    public boolean createCast(Context ctx) {
        Callable<Boolean> callable = () -> innerCreateCast(ctx);
        return execute(callable);
    }
    public boolean releaseCast() {
        Callable<Boolean> callable = () -> innerReleaseCast();
        return execute(callable);
    }
}