function show(type)
{
    count = 0;
    for (var key in methods) {    
        var row = document.getElementById(key);
        if (row != null)
	      {
	      	if ((methods[key] &  type) != 0) {
	            row.style.display = '';
	            row.className = (count++ % 2) ? rowColor : altColor;
	        }
	        else
	            row.style.display = 'none';
	      }
    }
    
    updateTabs(type);
    updateTabs1(type);
    updateTabs2(type);
}

function updateTabs(type)
{
    for (var value in tabs) {
        var sNode = document.getElementById(tabs[value][0]);
        if (sNode != null)
	      {
	        var spanNode = sNode.firstChild;
	        
	        if (value == type) {
	            sNode.className = activeTableTab;
	            spanNode.innerHTML = tabs[value][1];
	        }
	        else {
	            sNode.className = tableTab;
	            spanNode.innerHTML = "<a href=\"javascript:show("+ value + ");\">" + tabs[value][1] + "</a>";
	        }
	      }
    }
}

function updateTabs1(type)
{
    for (var value in tabs1) {
        var sNode = document.getElementById(tabs1[value][0]);
        if (sNode != null)
		    {
	        var spanNode = sNode.firstChild;
	        
	        if (value == type) {
	            sNode.className = activeTableTab;
	            spanNode.innerHTML = tabs1[value][1];
	        }
	        else {
	            sNode.className = tableTab;
	            spanNode.innerHTML = "<a href=\"javascript:show("+ value + ");\">" + tabs1[value][1] + "</a>";
	        }
	      }
    }
}

function updateTabs2(type)
{
    for (var value in tabs2) {
        var sNode = document.getElementById(tabs2[value][0]);
        if (sNode != null)
	      {
	        var spanNode = sNode.firstChild;
	        
	        if (value == type) {
	            sNode.className = activeTableTab;
	            spanNode.innerHTML = tabs2[value][1];
	        }
	        else {
	            sNode.className = tableTab;
	            spanNode.innerHTML = "<a href=\"javascript:show("+ value + ");\">" + tabs2[value][1] + "</a>";
	        }
	      }
    }
}