var tableData = [];

var win = Ti.UI.createWindow({ backgroundColor: 'yellow' });

var table = Ti.UI.createTableView({ objName: 'table' });

for (var i = 0; i < 50; i++)
{
  var row = Ti.UI.createTableViewRow({
    leftImage: 'file:///app/native/mac_labs_icon.png',
    title: String.format('row%d', i)
  });

  tableData.push(row);
}

table.setData(tableData);

win.add(table);
win.open();