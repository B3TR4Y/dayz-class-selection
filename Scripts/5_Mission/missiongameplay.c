modded class MissionGameplay {
	
	ref ClassMenu m_ClassMenu;
	ref array<ref JsonClassData> m_AvailableClasses;
	ref JsonConfig m_ClassSelectionConfig;

	void MissionGameplay()
	{
		GetRPCManager().SendRPC("ClassSelection", "RequestConfig", null, true);
		GetRPCManager().AddRPC("ClassSelection", "SyncAvailableClasses", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("ClassSelection", "SyncConfig", this, SingeplayerExecutionType.Client);
	}
	
	override void OnKeyPress( int key ) {
		super.OnKeyPress(key);
	
		switch ( key ) {
			case ClassSelectionUtils.StringToKeyCode(m_ClassSelectionConfig.keyToOpen):
				if(!m_ClassSelectionConfig.showClassSelectOnRespawnOnly) GetClassMenu().Toggle();
			break;
			default:
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if(m_Initialized  && !IsPaused() && player && player.IsPlayerLoaded() && !IsPlayerRespawning() && player.IsAlive()) {
			if(!HasSelectedClass()) {
				GetClassMenu().Show();
			}
		}
		else {
			GetClassMenu().Hide();
		}
	}
	
	void SyncAvailableClasses(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target )
	{
	    Param1<array<ref JsonClassData>> classes;
	    if ( !ctx.Read( classes ) ) return;
		
	    if( type == CallType.Client )
	    {
	        Print( "ClassSelection - Sync Classes!" );
	        m_AvailableClasses = classes.param1;
			GetClassMenu();
	    }
	}
	
	void SyncConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target )
	{
	    Param1<ref JsonConfig> config;
	    if ( !ctx.Read( config ) ) return;
		
	    if( type == CallType.Client )
	    {
	        Print( "ClassSelection - Sync Config!" );
	        m_ClassSelectionConfig = config.param1;
	    }
	}
	
	bool HasSelectedClass(bool returnAvailable = false) {
		if(m_AvailableClasses) {
			foreach(ref JsonClassData classData: m_AvailableClasses) {
				if(classData.selected) {
					return true;
				}
			}
		}
		if(returnAvailable) return false;
		
		return GetClassMenu().selectedClass;
	}
	
	private ref ClassMenu GetClassMenu() {
		if ( !m_ClassMenu ) {
			m_ClassMenu = new ClassMenu();
			m_ClassMenu.Init();
		}
		
		m_ClassMenu.SetAvailableClasses(m_AvailableClasses);
		m_ClassMenu.SetConfig(m_ClassSelectionConfig);
		m_ClassMenu.SetSelectedClass(HasSelectedClass(true));
		
		return m_ClassMenu;
	}
}