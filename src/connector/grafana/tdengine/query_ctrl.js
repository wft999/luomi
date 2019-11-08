import {QueryCtrl} from 'app/plugins/sdk';
import './css/query-editor.css!'

export class GenericDatasourceQueryCtrl extends QueryCtrl {

	  constructor($scope, $injector)  {
	    super($scope, $injector);

	    this.scope = $scope;
	  }
	  
	  generateSQL(query) {
          //this.lastGenerateSQL = this.datasource.generateSql(this.target.sql, this.panelCtrl.range.raw.from, this.panelCtrl.range.raw.to, this.panelCtrl.intervalMs);
          this.lastGenerateSQL = this.datasource.generateSql(this.target.sql, this.panelCtrl.range.from.toISOString(), this.panelCtrl.range.to.toISOString(), this.panelCtrl.intervalMs);
          this.showGenerateSQL = !this.showGenerateSQL;
        }
}

GenericDatasourceQueryCtrl.templateUrl = 'partials/query.editor.html';
