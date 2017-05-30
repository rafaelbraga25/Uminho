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
    public sealed partial class ResultsPage : Page
    {
        private readonly string SEARCH_STRING = "SearchString";
        private DispatcherTimer scrollTimer;
        //private List<Establishment> establishments;


        public ResultsPage()
        {
            this.InitializeComponent();
            
            ResultButton r = new ResultButton();
            r.Tapped += new TappedEventHandler(resultButtonTapped);

            scrollTimer = new DispatcherTimer();
            scrollTimer.Interval = new TimeSpan(0, 0, 0, 0, 800);
            scrollTimer.Tick += scrollTick;

            this.resultsPanel.Children.Add(r);
        }


        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            /// Obtêm-se os parâmetros de entrada da página da seguinte
            /// maneira:
            /// var params = (cast)e.Paremeter;

            scrollTimer = new DispatcherTimer();
            scrollTimer.Interval = new TimeSpan(0, 0, 0, 0, 800);
            scrollTimer.Tick += scrollTick;
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


        private void homeButtonTapped(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(SearchPage));
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
            }
        }


        private void voiceButtonPointerEntered(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.BorderBrush = AppUtilities.getSolidColorBrush("#FF000000");
            this.voiceSearchSymbol.Foreground = AppUtilities.getSolidColorBrush("#FF000000");
        }


        private void voiceButtonPointerExited(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");
            this.voiceSearchSymbol.Foreground = AppUtilities.getSolidColorBrush("#FFB3B3B3");
        }


        private void voiceButtonTapped(object sender, RoutedEventArgs e)
        {
            /// <summary>
            /// 
            /// Pode-se iniciar a pesquisa de voz a partir daqui
            /// 
            /// </summary>
        }


        private void optionsButtonPointerEntered(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;
         
            b.BorderBrush = AppUtilities.getSolidColorBrush("#FF000000");
            this.optionsSearchSymbol.Foreground = AppUtilities.getSolidColorBrush("#FF000000");
        }


        private void optionsButtonPointerExited(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");
            this.optionsSearchSymbol.Foreground = AppUtilities.getSolidColorBrush("#FFB3B3B3");
        }


        private void optionsButtonTapped(object sender, RoutedEventArgs e)
        {
            /// <summary>
            /// 
            /// Fazer filtragem da pesquisa
            /// 
            /// </summary>
        }


        private void resultButtonTapped(object sender, RoutedEventArgs e)
        {
            ResultButton r = sender as ResultButton;

            /// Através disto consegue-se o índice do botão e pode-se selecionar
            /// o estabelecimento da lista
            /// index = r.getIndex();
        }


        private void scrollViewerViewChanged(object sender, object e)
        {
            ScrollViewer s = sender as ScrollViewer;
            var verticalOffset = s.VerticalOffset;
            var maxVerticalOffset = s.ScrollableHeight;

            s.VerticalScrollBarVisibility = ScrollBarVisibility.Visible;
            scrollTimer.Start();

            if (maxVerticalOffset < 0 || verticalOffset == maxVerticalOffset)
            {
                /// Fez-se scroll até ao fundo da página, carregam-se mais
                /// estabelecimentos
            }
        }


        private void scrollTick(object sender, object e)
        {
            scrollTimer.Stop();
            resultsPageScrollViewer.VerticalScrollBarVisibility = ScrollBarVisibility.Hidden;
        }
    }
}
