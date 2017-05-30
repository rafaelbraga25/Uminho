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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Chewie
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private readonly string USER_NAME_STRING = "UserNameString";
        private readonly string DEFAULT_PASSWORD_STRING = "DefaultPasswordString";


        public MainPage()
        {
            this.InitializeComponent();
        }


        private void userTextBoxGotFocus(object sender, RoutedEventArgs e)
        {
            TextBox t = sender as TextBox;

            userTextBoxBorder.BorderBrush = AppUtilities.getSolidColorBrush("#FF000000");

            if (t.Text == AppUtilities.getResourceString(USER_NAME_STRING))
            {
                t.Text = "";
            }
        }


        private void userTextBoxLostFocus(object sender, RoutedEventArgs e)
        {
            TextBox t = sender as TextBox;

            userTextBoxBorder.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");

            if (t.Text == "")
            {
                t.Text = AppUtilities.getResourceString(USER_NAME_STRING);
            }
        }


        private void passwordTextBoxGotFocus(object sender, RoutedEventArgs e)
        {
            PasswordBox t = sender as PasswordBox;

            passwordTextBoxBorder.BorderBrush = AppUtilities.getSolidColorBrush("#FF000000");

            if (t.Password == AppUtilities.getResourceString(DEFAULT_PASSWORD_STRING))
            {
                t.Password = "";
            }
        }


        private void passwordTextBoxLostFocus(object sender, RoutedEventArgs e)
        {
            PasswordBox t = sender as PasswordBox;

            passwordTextBoxBorder.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");

            if (t.Password == "")
            {
                t.Password = AppUtilities.getResourceString(DEFAULT_PASSWORD_STRING);
            }
        }


        private void loginTextBoxTextChanged(object sender, RoutedEventArgs e)
        {
            if (loginUserBox.Text != "" && loginUserBox.Text != "Nome de Utilizador" && loginPasswordBox.Password != "")  
            {
                InitSessionButton.IsEnabled = true;
                InitSessionButton.Foreground = AppUtilities.getSolidColorBrush("#FF000000");
                InitSessionButton.BorderBrush = AppUtilities.getSolidColorBrush("#FF000000");
            }
            else
            {
                InitSessionButton.IsEnabled = false;
                InitSessionButton.Foreground = AppUtilities.getSolidColorBrush("#FFE6E6E6");
                InitSessionButton.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");
            }
        }


        private void initSessionButtonTapped(object sender, RoutedEventArgs e)
        {
            TextBox t = this.FindName("loginUserBox") as TextBox;
            PasswordBox p = this.FindName("loginPasswordBox") as PasswordBox;

            /// <summary>
            /// userName = t.Text
            /// password = p.Password
            /// 
            /// Código de autenticação do login pode-se fazer a partir daqui 
            /// com estes dois campos.
            /// 
            /// </summary>


            // Depois da autentição navega-se para a página da pesquisa
            this.Frame.Navigate(typeof(SearchPage));
        }


        private void registerPointerEntered(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.Foreground = new SolidColorBrush(Windows.UI.Colors.Black);
            b.BorderBrush = new SolidColorBrush(Windows.UI.Colors.Black);

            Window.Current.CoreWindow.PointerCursor = new Windows.UI.Core.CoreCursor(Windows.UI.Core.CoreCursorType.Hand, 0);
        }


        private void registerPointerExited(object sender, RoutedEventArgs e)
        {
            Button b = sender as Button;

            b.Foreground = AppUtilities.getSolidColorBrush("#FFB3B3B3");
            b.BorderBrush = AppUtilities.getSolidColorBrush("#FFB3B3B3");

            Window.Current.CoreWindow.PointerCursor = new Windows.UI.Core.CoreCursor(Windows.UI.Core.CoreCursorType.Arrow, 0);
        }
    }
}
