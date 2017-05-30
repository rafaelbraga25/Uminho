using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Chewie
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class SearchPage : Page
    {
        private readonly string SEARCH_STRING = "SearchString";


        public SearchPage()
        {
            this.InitializeComponent();
        }


        private void barButtonPointerEntered(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.Foreground = AppUtilities.getSolidColorBrush("#FFE4593A");
            b.BorderBrush = AppUtilities.getSolidColorBrush("#FFE4593A");
        }


        private void barButtonPointerExited(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.Foreground = AppUtilities.getSolidColorBrush("#FFB3B3B3");
            b.BorderBrush = AppUtilities.getSolidColorBrush("#FF3F3F3F");
        }


        private void sugestionsButtonTapped(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(sugestionsPage));
        }


        private void searchBoxGotFocus(object sender, RoutedEventArgs e)
        {
            TextBox t = sender as TextBox;

            if (t.Text == AppUtilities.getResourceString(SEARCH_STRING))
            {
                t.Text = "";
            }
        }


        private void searchBoxLostFocus(object sender, RoutedEventArgs e)
        {
            TextBox t = sender as TextBox;

            if (t.Text == "")
            {
                t.Text = AppUtilities.getResourceString(SEARCH_STRING);
            }

            t.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");
        }


        private void searchBoxKeyDown(object sender, KeyRoutedEventArgs e)
        {
            TextBox t = sender as TextBox;

            if (e.Key == Windows.System.VirtualKey.Enter && t.Text != "")
            {
                /// <summary>
                /// 
                /// pesquisa = t.Text
                /// Iniciar pesquisa de texto aqui
                /// 
                /// </summary>

                /// Pode-se invocar esta função com parâmetros adicionais,
                /// neste caso, evia-se a lista de resultados da pesquisa
                this.Frame.Navigate(typeof(ResultsPage));
            }
        }


        private void voiceButtonPointerEntered(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.BorderBrush = AppUtilities.getSolidColorBrush("#FF000000");
            voiceSearchSymbol.Foreground = AppUtilities.getSolidColorBrush("#FF000000");
        }


        private void voiceButtonPointerExited(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");
            voiceSearchSymbol.Foreground = AppUtilities.getSolidColorBrush("#FFB3B3B3");
        }


        private void voiceButtonTapped(object sender, RoutedEventArgs e)
        {
            /// <summary>
            /// 
            /// Pode-se iniciar a pesquisa de voz a partir daqui
            /// 
            /// </summary>
        }
    }
}
