using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Diagnostics;

namespace Launcher
{
    public partial class Form1 : Form
    {
        private readonly Dictionary<string, Process> _processDictionary = new Dictionary<string, Process>();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1Load(object sender, EventArgs e)
        {
            ProcessComboBoxDropDown(null, null);
        }

        private void ProcessComboBoxDropDown(object sender, EventArgs e)
        {
            processComboBox.Items.Clear();

            PopulateProcessDictionary("wow");

            processComboBox.Items.AddRange(_processDictionary.Keys.ToArray<Object>());
        }

        private void PopulateProcessDictionary(string processName)
        {
            _processDictionary.Clear();

            Process[] processes = Process.GetProcessesByName(processName);

            foreach (Process process in processes)
            {
                string keyString = process.ProcessName +"<"+process.Id+">";
                _processDictionary.Add(keyString, process); 
            }
        }

        private void LaunchButtonClick(object sender, EventArgs e)
        {
            if (processComboBox.SelectedIndex < 0)
                return;

            Process process = _processDictionary[processComboBox.SelectedItem.ToString()];
 
        }
    }
}
