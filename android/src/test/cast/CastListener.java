package test.cast;

import android.util.Log;

import java.nio.ByteBuffer;
import java.util.Optional;

import me.clarius.sdk.Button;
import me.clarius.sdk.Cast;
import me.clarius.sdk.PosInfo;
import me.clarius.sdk.ProbeInfo;
import me.clarius.sdk.ProcessedImageInfo;
import me.clarius.sdk.RawImageInfo;
import me.clarius.sdk.SpectralImageInfo;

class CastListener implements Cast.Listener {
    private static final String TAG = "CastListener";

    CastListener() {
    }

    @Override
    public void error(String s) {
        Log.e(TAG, s);
    }

    @Override
    public void freeze(boolean b) {
    }

    @Override
    public void initializationResult(boolean result) {
        Log.d(TAG, String.format("initializationResult %b", result));
    }

    @Override
    public void connectionResult(boolean b) {
        Log.d(TAG, String.format("connectionResult %b", b));
    }

    @Override
    public void disconnectionResult(boolean b) {
    }

    @Override
    public void newProcessedImage(ByteBuffer byteBuffer, ProcessedImageInfo processedImageInfo, PosInfo[] posInfos) {

    }

    @Override
    public void newRawImageFn(ByteBuffer byteBuffer, RawImageInfo rawImageInfo, PosInfo[] posInfos) {

    }

    @Override
    public void newSpectralImageFn(ByteBuffer byteBuffer, SpectralImageInfo spectralImageInfo) {

    }

    @Override
    public void firmwareVersionRetrieved(Optional<String> optional, Object o) {

    }

    @Override
    public void probeInfoRetrieved(Optional<ProbeInfo> optional, Object o) {

    }

    @Override
    public void userFunctionResult(boolean b, Object o) {
    }

    @Override
    public void buttonPressed(Button button, int i) {

    }
}
