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
    public void buttonPressed(Button button, int i) {

    }

    @Override
    public void error(String s) {
        Log.e(TAG, s);
    }

    @Override
    public void freeze(boolean b) {
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
    public void progress(int progress) {
        
    }
}
