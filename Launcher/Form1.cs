using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Launcher
{
    public partial class Form1 : Form
    {
        private Dictionary<string, Process> processDictionary = new Dictionary<string, Process>();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            processComboBox_DropDown(null, null);
        }

        private void processComboBox_DropDown(object sender, EventArgs e)
        {
            processComboBox.Items.Clear();

            populateProcessDictionary("wow");

            processComboBox.Items.AddRange(processDictionary.Keys.ToArray<Object>());
        }

        private void populateProcessDictionary(string processName)
        {
            processDictionary.Clear();

            Process[] processes = Process.GetProcessesByName(processName);

            foreach (Process process in processes)
            {
                string keyString = process.ProcessName +"<"+process.Id+">";
                processDictionary.Add(keyString, process); 
            }
        }
    }
}
