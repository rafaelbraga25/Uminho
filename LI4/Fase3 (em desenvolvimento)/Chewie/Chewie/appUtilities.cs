using System;
using Windows.UI.Xaml.Media;


public partial class AppUtilities
{
    public static SolidColorBrush getSolidColorBrush(string hex)
    {
        hex = hex.Replace("#", string.Empty);

        byte a = (byte)(Convert.ToUInt32(hex.Substring(0, 2), 16));
        byte r = (byte)(Convert.ToUInt32(hex.Substring(2, 2), 16));
        byte g = (byte)(Convert.ToUInt32(hex.Substring(4, 2), 16));
        byte b = (byte)(Convert.ToUInt32(hex.Substring(6, 2), 16));

        SolidColorBrush myBrush = new SolidColorBrush(Windows.UI.Color.FromArgb(a, r, g, b));

        return myBrush;
    }


    public static string getResourceString(string resourceName)
    {
        string value = "";

        var loader = new Windows.ApplicationModel.Resources.ResourceLoader();

        value = loader.GetString(resourceName);

        return value;
    }
}