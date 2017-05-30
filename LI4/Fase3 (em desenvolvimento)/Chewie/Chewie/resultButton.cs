using System;
using System.Collections.Generic;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;


public partial class ResultButton : Grid
{
    private readonly uint MAX_STARS = 5;
    private readonly string ERROR_SOURCE = "ms-appx:///Assets/Square150x150Logo.scale-200.png";

    private Grid establishmentGrid;
    private Grid imageGrid;
    private Grid separatorGrid;
    private uint index;


    private void setEstablishmentGrid(string name, uint numStars)
    {
        uint i = 1;
        List<ColumnDefinition> columns = new List<ColumnDefinition>();
        ColumnDefinition textColumn = new ColumnDefinition();
        TextBlock t = new TextBlock();

        t.Text = name;
        t.Foreground = AppUtilities.getSolidColorBrush("#FFB3B3B3");
        t.FontSize = 14;
        Grid.SetColumn(t, 0);
        textColumn.Width = new GridLength(1.0, GridUnitType.Star);
        
        establishmentGrid = new Grid();
        establishmentGrid.ColumnDefinitions.Add(textColumn);
        establishmentGrid.Children.Add(t);

        for (; i <= MAX_STARS; i++)
        {
            SymbolIcon s = new SymbolIcon();
            s.Symbol = Symbol.Favorite;
            s.Width = 20;

            if (numStars >= i)
            {
                s.Foreground = AppUtilities.getSolidColorBrush("#FFE4593A");
            }
            else
            {
                s.Foreground = AppUtilities.getSolidColorBrush("#FFB3B3B3");
            }

            Grid.SetColumn(s, (int)i);
            ColumnDefinition c = new ColumnDefinition();
            c.Width = new GridLength(22.0);
            establishmentGrid.ColumnDefinitions.Add(c);
            establishmentGrid.Children.Add(s);
        }

        Grid.SetRow(establishmentGrid, 1);
        base.Children.Add(establishmentGrid);
    }


    private void setImageGrid(string source)
    {
        Image img = new Image();
        BitmapImage src;

        try
        {
            src = new BitmapImage(new Uri(string.Format(source), UriKind.RelativeOrAbsolute));
        }
        catch (System.ArgumentException)
        {
            src = new BitmapImage(new Uri(string.Format(ERROR_SOURCE), UriKind.RelativeOrAbsolute));
        }

        img.Source = src;

        imageGrid = new Grid();
        imageGrid.Children.Add(img);
        Grid.SetRow(imageGrid, 3);
        base.Children.Add(imageGrid);
    }


    private void setSeparatorGrid(double height, int row)
    {
        separatorGrid = new Grid();
        separatorGrid.Height = height;
        Grid.SetRow(separatorGrid, row);
        base.Children.Add(separatorGrid);
    }


    private void resultButtonPointerEntered(object sender, RoutedEventArgs e)
    {
        Window.Current.CoreWindow.PointerCursor = new Windows.UI.Core.CoreCursor(Windows.UI.Core.CoreCursorType.Hand, 0);
    }


    private void resultButtonPointerExited(object sender, RoutedEventArgs e)
    {
        Window.Current.CoreWindow.PointerCursor = new Windows.UI.Core.CoreCursor(Windows.UI.Core.CoreCursorType.Arrow, 0);
    }


    public ResultButton() : base()
    {
        base.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");
        base.BorderThickness = new Thickness(0, 2, 0, 2);
        base.Background = AppUtilities.getSolidColorBrush("#FFFFFFFF");

        RowDefinition r0 = new RowDefinition();
        RowDefinition r1 = new RowDefinition();
        RowDefinition r2 = new RowDefinition();
        RowDefinition r3 = new RowDefinition();
        RowDefinition r4 = new RowDefinition();

        base.RowDefinitions.Add(r0);
        base.RowDefinitions.Add(r1);
        base.RowDefinitions.Add(r2);
        base.RowDefinitions.Add(r3);
        base.RowDefinitions.Add(r4);

        this.setSeparatorGrid(5.0, 0);
        this.setEstablishmentGrid("fhjhdhjhfdhjf", 4);
        this.setSeparatorGrid(5.0, 2);
        this.setImageGrid("ms-appx:///Assets/chewie.png");
        this.setSeparatorGrid(10.0, 4);

        base.PointerEntered += resultButtonPointerEntered;
        base.PointerExited += resultButtonPointerExited;

        index = 0;
    }


    public uint getIndex()
    {
        return index;
    }
} 