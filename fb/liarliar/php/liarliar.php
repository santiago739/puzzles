<?php 

error_reporting(E_ERROR);

function print_table(&$graph_table, &$bloggers)
{
	foreach ($bloggers as $col_key => $col_val) 
	{
		echo "\t" . $col_val['name'];
	}
	echo "\n";

	foreach ($bloggers as $row_key => $row_val) 
	{
		echo $row_val['name'] . "\t";
		foreach ($bloggers as $col_key => $col_val) 
		{
			echo $graph_table[$row_key][$col_key] . "\t";
		}
		echo "\n";
	}	
}

$total_bloggers = 0;
$bloggers = array();
$bloggers_id = array();
$graph_table = array();
$selected_ids = array();


if ($argc != 2)
{
	exit(1);
}

$file_data = file_get_contents($argv[1]);

//var_dump($file_data);

$file_rows = split("\n", $file_data);

//var_dump($file_rows);

$i = 0; $j = 0; $k = 0;
foreach ($file_rows as $row) 
{
	$i++;
	if ($i === 1)
	{
		$total_bloggers = (int)$row;
	}
	else 
	{
		$blogger_data = split("[ \t]+", $row);
//		var_dump($blogger_data);
		if (count($blogger_data) == 2 && $k < $total_bloggers)
		{
			$id = $k + 1;
			$blogger_name = $blogger_data[0];
			$bloggers[$id]['name'] = $blogger_name;
			$bloggers[$id]['status'] = 'unknown';
			$bloggers[$id]['ready'] = false;
			$bloggers[$id]['accused'] = 0;
			$bloggers_id[$blogger_name] = $id;
			
			$total_accusations = (int)$blogger_data[1];
			$j = 0;
			$k++;
		}
		else 
		{
			if ($j < $total_accusations)
			{
				$bloggers[$id]['accusations'][] = $blogger_data[0];
			}
			$j++;
		}
	}
}

foreach	($bloggers as $blogger)
{
    //var_dump($blogger['accusations']);
    foreach ($blogger['accusations'] as $accusation) 
	{
        $acc_id = (int)$bloggers_id[$accusation];
        if ($acc_id > 0)
        {
            $bloggers[$acc_id]['accused'] += 1;
        }
    }
}

//var_dump($bloggers);


// Init graph table
/*
for ($i = 0; $i <= $total_bloggers; $i++)
{
	for ($j = 0; $j <= $total_bloggers; $j++)
	{
		$graph_table[$i][$j] = 0;
	}
}

// Build graph table
foreach ($bloggers as $row_key => $row_val) 
{
	foreach ($row_val['accusations'] as $accusation) 
	{		
		$col_id = (int)$bloggers_id[$accusation];
		if ($col_id > 0)
		{
			$graph_table[$row_key][$col_id] = 1;
		}
	}
}

print_table($graph_table, $bloggers);
echo "\n";
*/


//var_dump($bloggers);
foreach	($bloggers as $id => $blogger)
{
    //var_dump($blogger['name']);
    //var_dump($blogger['accused']);
    if ($blogger['accused'] == 0)
    {
        $selected_ids[] = $id;
    }
}

//var_dump($selected_ids);

foreach	($selected_ids as $sel_id)
{
    do_process($sel_id, 'non-liar', $bloggers, $bloggers_id);
    do_process($sel_id, 'liar', $bloggers, $bloggers_id);
}
//do_process(1, 'liar', $bloggers, $bloggers_id);
//do_process(1, 'non-liar', $bloggers, $bloggers_id);

function do_process($sel_id, $status, $bloggers, $bloggers_id)
{
    $total_liers = 0;
    $total_nonliers = 0;
    $total_bloggers = count($bloggers);
    $bloggers[$sel_id]['status'] = $status;
    
    foreach	($bloggers[$sel_id]['accusations'] as $accusation)
    {
        $acc_id = (int)$bloggers_id[$accusation];
        if ($bloggers[$sel_id]['status'] == 'non-liar')
        {
            $bloggers[$acc_id]['status'] = 'liar';
        }
        elseif ($bloggers[$sel_id]['status'] == 'liar')
        {
            $bloggers[$acc_id]['status'] = 'non-liar';
        }
    }
    $bloggers[$sel_id]['ready'] = true;
    $count_ready++;

    //var_dump($bloggers);

    $flag_do = true;
    //while ($flag_do)
    for ($i = $total_bloggers; $i > 0; $i--)
    {
        $count_ready = 0;
        foreach	($bloggers as &$blogger)
        {
            if ($blogger['ready'] == true)
            {
                //$count_ready++;
                continue;
            }
            
            if ($blogger['status'] == 'unknown')
            {
                continue;
            }
            
            foreach	($blogger['accusations'] as $accusation)
            {
                $acc_id = (int)$bloggers_id[$accusation];
                if ($bloggers[$acc_id]['ready'] == true)
                {
                    continue;
                }
                
                if ($bloggers[$acc_id]['status'] == 'unknown')
                {
                    if ($blogger['status'] == 'non-liar')
                    {
                        $bloggers[$acc_id]['status'] = 'liar';
                    }
                    elseif ($blogger['status'] == 'liar')
                    {
                        $bloggers[$acc_id]['status'] = 'non-liar';
                    }
                }
            }
            $blogger['ready'] = true;
            $count_ready++;
        }
        
        foreach	($bloggers as &$blogger)
        {
            if (($blogger['ready'] == false) && ($blogger['accused'] == 0))
            {
                foreach	($blogger['accusations'] as $accusation)
                {
                    $acc_id = (int)$bloggers_id[$accusation];
                    if ($bloggers[$acc_id]['ready'] == true)
                    {
                        if ($bloggers[$acc_id]['status'] == 'liar')
                        {
                            $blogger['status'] = 'non-liar';
                            //$blogger['ready'] = true;
                            //$count_ready++;
                        }
                        elseif ($bloggers[$acc_id]['status'] == 'non-liar')
                        {
                            $blogger['status'] = 'liar';
                            //$blogger['ready'] = true;
                            //$count_ready++;
                        }
                    }
                }
            }
        }
        
        if ($count_ready == $total_bloggers)
        {
            $flag_do = false;
        }
    }

    //var_dump($bloggers);

    foreach	($bloggers as &$blogger)
    {
        if ($blogger['status'] == 'liar')
        {
            $total_liers++;
        }
        elseif ($blogger['status'] == 'non-liar')
        {
            $total_nonliers++;
        }
    }

    echo "LIERS: " . $total_liers . "\n";
    echo "NON-LIERS: " . $total_nonliers . "\n";
}    







