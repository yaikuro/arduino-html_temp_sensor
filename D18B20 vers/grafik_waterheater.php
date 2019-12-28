<?php // content="text/plain; charset=utf-8"
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 5; URL=$url");  // Refresh the webpage every 5 seconds

require_once ('jpgraph/src/jpgraph.php');
require_once ('jpgraph/src/jpgraph_line.php');


$servername = "localhost";
$username = "root";
$password = "";
$dbname = "projek";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

$sql = "SELECT Temperatur, Waktu FROM waterheater";
$result = mysqli_query($conn, $sql);

while($row = mysqli_fetch_assoc($result)) {
    $temp[] = $row['Temperatur'];
		$waktu[] = $row['Waktu'];
    }


$datay1 = $temp;
//$datay2 = $humd;
//$datay3 = array(5,17,32,24);

// Setup the graph
$graph = new Graph(1000,500);
$graph->SetScale("textlin");

$theme_class=new UniversalTheme;

$graph->SetTheme($theme_class);
$graph->img->SetAntiAliasing(false);
$graph->title->Set('Temperature Water Heater');
$graph->SetBox(false);

$graph->SetMargin(70,70,36,63);

$graph->img->SetAntiAliasing();

$graph->yaxis->HideZeroLabel();
$graph->yaxis->HideLine(false);
$graph->yaxis->HideTicks(false,false);

$graph->xgrid->Show();
$graph->xgrid->SetLineStyle("solid");
$graph->xaxis->SetTickLabels($waktu);
$graph->xgrid->SetColor('#E3E3E3');

// Create the first line
$p1 = new LinePlot($datay1);
$graph->Add($p1);
$p1->SetColor("#6495ED");
$p1->SetLegend('Temperature');


$graph->legend->SetFrameWeight(1);

// Output line
$graph->Stroke();

?>
