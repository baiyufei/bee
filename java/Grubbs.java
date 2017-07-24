import java.util.ArrayList;

/**
 * Grubbs 方法剔除异常数据
 */
public class Grubbs {
    /**
     * 设置p
     *
     * @param p 输入0.95或者0.99,默认0.95
     */
    private static void setP(double p) {
        if (p == 0.95)
            critical = Critical_095;
        else if (p == 0.99)
            critical = Critical_099;
    }

    // p = 0.95 时的 Grubbs 表
    private static final double[] Critical_095 = {1.135, 1.463, 1.672, 1.822, 1.938, 2.032, 2.110, 2.176, 2.234, 2.285,
            2.331, 2.371, 2.409, 2.443, 2.475, 2.504, 2.532, 2.557};

    // p = 0.99 时得 Grubbs 表
    private static final double[] Critical_099 = {1.155, 1.492, 1.749, 1.944, 2.097, 2.231, 2.323, 2.410, 2.485, 2.550,
            2.607, 2.659, 2.705, 2.747, 2.785, 2.821, 2.854, 2.884};
    private static double[] critical = Critical_095;

    /**
     * Grubbs 方法剔除异常数据
     *
     * @param input 数据数组
     * @return 剔除后的数据数组
     */
    public static double[] excludeOutlier(double[] input) {
        ArrayList<Double> list = new ArrayList<Double>();
        for (int i = 0; i < input.length; i++) {
            list.add(input[i]);
        }
        ArrayList<Double> out = excludeOutlier(list);
        double[] ret = new double[out.size()];
        for (int i = 0; i < out.size(); i++) {
            ret[i] = out.get(i);
        }
        return ret;
    }

    /**
     * Grubbs 方法剔除异常数据
     *
     * @param input 数据ArrayList
     * @return 剔除后的数据Arraylist
     */
    public static ArrayList<Double> excludeOutlier(ArrayList<Double> input) {
        int len = input.size();
        if (len < 3)
            return input;

        int i_min = 0;
        int i_max = 0;
        double min = input.get(0);
        double max = input.get(0);
        double avg = 0; // 均值
        double var = 0; // 方差

        for (int i = 0; i < len; i++) {
            double value = input.get(i);
            if (value > max) {
                max = value;
                i_max = i;
            } else if (value < min) {
                min = value;
                i_min = i;
            }
            avg += value;
            var += value * value;
        }
        avg = avg / len;
        var = var / len;
        double sd = Math.sqrt(var - avg * avg);   // 标准差

        double tar;
        int i_tar;
        if (max - avg > avg - min) {
            // 可疑值是最大值
            tar = max - avg;
            i_tar = i_max;
        } else {
            // 可疑值是最小值
            tar = avg - min;
            i_tar = i_min;
        }

        double g = tar / sd;
        if (g > critical[len - 3]) {
            // 异常数据，需要剔除
            input.remove(i_tar);
            return excludeOutlier(input);
        }

        return input;
    }
}
